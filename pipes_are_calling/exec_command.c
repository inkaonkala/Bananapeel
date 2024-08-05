/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/07/26 14:53:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	shut_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}


static void	redirect_input(t_bananas *bana, int index)
{
		if (index == 0 && bana->fd_input != -1)
		{
			dup2(bana->fd_input, STDIN_FILENO);
			close(bana->fd_input);
		}
		else if (index > 0)
		{
			dup2(bana->prev_fd[0], STDIN_FILENO);
			close(bana->prev_fd[0]);
		}
}

static void	redirect_putput(t_bananas *bana, int fd[2], int index)
{
	if (index == bana->tok_num && bana->fd_output != -1)
	{
		dup2(bana->fd_output, STDOUT_FILENO);
		close(bana->fd_output);
	}
	else if(index < bana->tok_num - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		shut_fd(fd);
	}
}

static void	execute_command(t_bananas *bana, char **envp, int index)
{
	if(bana->cmd_paths[index])
	{
		execve(bana->cmd_paths[index], &bana->cmd_args[index], envp);

	}
	else
		perror("		Bananas! Can't find your command to execve");
}


bool	fork_it(t_bananas *bana, int fd[2], pid_t *pid, int index)
{
	if (index < bana->tok_num)
	{
		if(pipe(fd) == -1)
		{
			perror("No pipes to fork the banananas\n");
			return (false);
		}
	}

	*pid = fork();
	if (*pid == -1)
	{
		perror("I don't use fork to eat banananas\n");
		if (index < bana->tok_num)
			shut_fd(fd);
		return (false);
	}
	return (true);
}

/*
static bool	wait_it(t_bananas *bana, pid_t pid, int index, int *fd)
{
	int	status;

	close(fd[0]);

	if (index == bana->tok_num - 1)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (false);
		}
		//if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		//	return (false);
	}
	return (true);
}
*/

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;
	int		first;

	last = (index == bana->tok_num);
	first = (index == 0);

	if (!fork_it(bana, fd, &pid, index))
		return (false);
	

	if (pid == 0)
	{
		redirect_input(bana, index);
		redirect_putput(bana, fd, index);
		execute_command(bana, envp, index);
		//exit(EXIT_FAILURE);
	}
	else
	{
		if (index > 0)
			close(bana->prev_fd[0]);

		if (!last)
		{
			bana->prev_fd[0] = fd[0];
			close(fd[1]);
		}
	}
	return (true);
}
