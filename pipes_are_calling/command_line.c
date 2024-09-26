/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:58 by iniska            #+#    #+#             */
/*   Updated: 2024/09/26 15:20:26 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	path_handler(t_bananas *bana, char **envp, int i)
{
	char	**cmd;

	cmd = ft_split(bana->token[i], ' ');
	if (!cmd)
	{
		free_line(bana->cmd_paths, bana->tok_num);
		bana->cmd_paths = NULL;
		return (false);
	}
	bana->cmd_paths[i] = get_path(cmd[0], envp);
	if (bana->cmd_paths[i] == NULL)
		bana->nonsense = true;
	free_line(cmd, -1);
	return (true);
}

static bool	init_path(t_bananas *bana)
{
	bana->cmd_paths = ft_calloc(bana->tok_num, sizeof(char *));
	if (!bana->cmd_paths)
	{
		bana->cmd_paths = NULL;
		return (false);
	}
	return (true);
}

bool	parse_cmd_line(t_bananas *bana, char **envp)
{
	int		i;
	char	**cmd;

	i = 0;
	if (!init_path(bana))
		return (false);
	while (i < bana->tok_num)
	{	
		if (!check_specials(bana->token[i]))
		{
			if (!path_handler(bana, envp, i))
				return (false);
			i++;
		}
		else
			token_cleaner(bana, i);
	}
	return (true);
}
