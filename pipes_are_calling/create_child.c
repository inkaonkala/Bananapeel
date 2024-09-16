/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:43:34 by iniska            #+#    #+#             */
/*   Updated: 2024/09/16 12:08:16 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		redirect_input(bana, index);
		redirect_putput(bana, fd, index);
	}
	execute_command(bana, envp, index);
	exit (1);
}

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;
	int		status;

	last = (index == bana->tok_num - 1);
	if (!fork_it(bana, fd, &pid, index))
		return (false);
	if (pid == 0)
		input_n_putput(bana, envp, index, fd);
	else
	{
		if (index > 0)
			close(bana->prev_fd[0]);
		if (!last)
		{
			bana->prev_fd[0] = fd[0];
			close(fd[1]);
		}
		else
		{
			shut_fd(fd);
			waitpid(pid, &status, 0);
			bana->last_exit_status = WEXITSTATUS(status);
		}
	}
	return (true);
}
