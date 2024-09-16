/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:58 by iniska            #+#    #+#             */
/*   Updated: 2024/09/16 12:08:53 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	init_path(t_bananas *bana)
{
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
			i++;
		}
		else
			token_cleaner(bana, i);
	}
	return (true);
}
