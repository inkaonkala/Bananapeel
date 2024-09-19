/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:58 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 10:43:56 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	path_handler(t_bananas *bana, char **envp, char *path, int i)
{
	char	**cmd;

	cmd = ft_split(bana->token[i], ' ');
	if (!cmd)
	{
		free_line(bana->cmd_paths, bana->tok_num);
		bana->cmd_paths = NULL;
		return (false);
	}
	path = get_path(cmd[0], envp);
	bana->cmd_paths[i] = path;
	free_line(cmd, -1);
	return (true);
}

static bool	init_path(t_bananas *bana)
{
	int	i;

	i = bana->tok_num;
	if (i > 3)
		i--;
	bana->cmd_paths = ft_calloc(bana->tok_num, sizeof(char *));
	if (!bana->cmd_paths)
		return (false);
	return (true);
}

bool	parse_cmd_line(t_bananas *bana, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	if (!init_path(bana))
		return (false);
	while (i < bana->tok_num)
	{	
		if (!check_specials(bana->token[i]))
		{
			if (!path_handler(bana, envp, path, i))
				return (false);
			i++;
		}
		else
			token_cleaner(bana, i);
	}
	return (true);
}

/*
bool	parse_cmd_line(t_bananas *bana, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	if (!init_path(bana))
		return (false);
	while (i < bana->tok_num)
	{	
		if (!check_specials(bana->token[i]))
		{
			if (!path_handler(bana, envp, path, i))
				return (false);
			if(bana->cmd_paths[i] == NULL)
			{
				printf("Your command is bananas!\n");
				token_cleaner(bana, i);
			}
			else
				i++;
		}
		else
			token_cleaner(bana, i);
	}
	return (true);
}

*/
