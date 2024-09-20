/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:22:34 by iniska            #+#    #+#             */
/*   Updated: 2024/09/20 16:56:12 by jbremser         ###   ########.fr       */
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
			perror("Bananas! Malloc fails in pipe helper\n");
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
			perror("Bananas! Malloc failed in pipes\n");
			clean_struct(bana);
			exit(2);
		}
		pipe_helper(bana->pipes, 0, num_pipes);
	}
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
}
