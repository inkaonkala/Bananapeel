/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:22:34 by iniska            #+#    #+#             */
/*   Updated: 2024/09/09 12:37:47 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_helper(int **pipes, int i, int num_pipes)
{
	if (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("Malloc fails in pipe helper\n");
			return ;
		}
		pipe_helper(pipes, i + 1, num_pipes);
	}
}

void	init_pipes(t_bananas *bana)
{
	int	num_pipes;

	num_pipes = bana->tok_num - 1;
	if (num_pipes == 0)
	{
		bana->pipes = malloc(sizeof(int *) * num_pipes);
		if (!bana->pipes)
		{
			perror("Malloc failed in pipes");
			clean_struct(bana);
			exit(-1);
		}
		pipe_helper(bana->pipes, 0, num_pipes);
	}
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
}
