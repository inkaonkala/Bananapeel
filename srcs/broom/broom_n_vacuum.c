/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broom_n_vacuum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:23:36 by iniska            #+#    #+#             */
/*   Updated: 2024/09/27 11:51:30 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	clean_pipestuff(t_bananas *bana)
{
	int	b;

	b = 0;
	if (bana->cmd_args != NULL)
	{
		while (bana->cmd_args[b] != NULL)
		{
			free(bana->cmd_args[b]);
			bana->cmd_args[b] = NULL;
			b++;
		}
		free(bana->cmd_args);
		bana->cmd_args = NULL;
	}
}

void	clean_files(t_bananas *bana)
{
	if (bana->in_files != NULL)
	{
		free(bana->in_files);
		bana->in_files = NULL;
	}
	if (bana->out_files != NULL)
	{
		free(bana->out_files);
		bana->out_files = NULL;
	}
}

void	clean_struct(t_bananas *bana)
{
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	clean_files(bana);
	clean_pipestuff(bana);
	if (bana->pipes != NULL)
	{
		free(bana->pipes);
		bana->pipes = NULL;
	}
	bana->tok_num = 0;
	bana->infile_count = 0;
	bana->outfile_count = 0;
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
}

void	token_cleaner(t_bananas *bana, int i)
{
	if (bana->token == NULL || i >= bana->tok_num)
		return ;
	free(bana->token[i]);
	bana->token[i] = NULL;
	while (i < bana->tok_num - 1)
	{
		bana->token[i] = bana->token[i + 1];
		i++;
	}
	bana->tok_num--;
	bana->token[bana->tok_num] = NULL;
	if (bana->tok_num == 0)
	{
		free(bana->token);
		bana->token = NULL;
	}
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
