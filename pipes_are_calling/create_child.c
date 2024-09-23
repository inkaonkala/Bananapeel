/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:43:34 by iniska            #+#    #+#             */
/*   Updated: 2024/09/23 10:59:29 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	hangers(t_bananas *bana)
{
	if (bana->tok_num < 2 && strncmp(bana->token[0], "cat", 3) != 0)
		return (false);
	else if (bana->tok_num < 2 && strncmp(bana->token[0], "wc", 2) != 0)
		return (false);
	else if (bana->tok_num < 2 && strncmp(bana->token[0], "grep", 4) != 0)
		return (false);
	else
		return (true);
}

static void	input_n_putput(t_bananas *bana, char **envp, int index, int fd[2])
{
	if (bana->is_rdr)
	{
		if (!redirect_file_input(bana))
			redirect_input(bana, index);
		redirect_file_putput(bana);
	}
	else
	{
		if (hangers(bana))
		{
			redirect_input(bana, index);
			redirect_putput(bana, fd, index);
		}
	}
	execute_command(bana, envp, index);
	exit (1);
}

static void	fd_handler(t_bananas *bana, int index, int last, int fd[2])
{
	if (index > 0)
		close(bana->prev_fd[0]);
	if (!last)
	{
		bana->prev_fd[0] = fd[0];
		close(fd[1]);
	}
}

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;

	last = (index == bana->tok_num - 1);
	if (!fork_it(bana, fd, &pid, index))
		return (false);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		input_n_putput(bana, envp, index, fd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (index > 0 || !last)
			fd_handler(bana, index, last, fd);
		else
			shut_fd(fd);
	}
	return (true);
}
