/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:41:50 by iniska            #+#    #+#             */
/*   Updated: 2024/05/06 16:42:50 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char ***paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(*paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (*paths[i] != NULL)
				free((*paths[i]));
			i++;
		}
	}
	free (*paths);
	*paths = NULL;
}

void	free_line(char **paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free(paths[i]);
			i++;
		}
	}
	free(paths);
	paths = NULL;
}

void	free_char_array(char ***paths, int arc)
{
	free_array(paths, arc);
}

void	clean_n_errors(t_bananas *bana)
{
	if (bana->fd_input != -1)
		close(bana->fd_input);
	if (bana->fd_output != -1)
		close(bana->fd_output);
	if (bana->cmd_paths != NULL)
		free_line(bana->cmd_paths, bana->tok_num - 1);
	if (bana->token != NULL)
		free_array(&bana->token, bana->tok_num - 1);
	free(bana);
}
