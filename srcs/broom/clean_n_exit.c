/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/26 11:33:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_path(t_bananas *bana)
{
	int	b;

	b = 0;
	if (bana->cmd_paths != NULL)
	{
		while (bana->cmd_paths[b] != NULL)
		{
			free(bana->cmd_paths[b]);
			bana->cmd_paths[b] = NULL;
			b++;
		}
		free(bana->cmd_paths);
		bana->cmd_paths = NULL;
	}
}

void	exiting(t_bananas *bana, int i)
{
	clean_banana(bana);
	exit(i);
}

void	clean_banana(t_bananas *bana)
{
	clean_struct(bana);
	//clean_path(bana);
	free_env(&bana->env);
	if (bana->envp)
	{
		if (bana->envp[0])
		{
			free_char_array(bana->envp);
		}
	}
}

bool	return_n_free(char **tokens)
{
	free_char_array(tokens);
	return (false);
}
