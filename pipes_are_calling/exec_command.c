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

bool	fork_it(t_bananas *bana, int fd[2], pid_t *pid, int index)
{
	//if (bana(fd) == -1)
//		return (false);
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		shut_fd(fd);
		return (false);
	}
	if (*pid == 0)
	{
		if (index == 0)
			dup2(bana->fd_input, STDIN_FILENO);
		if (index == bana->tok_num - 1)
			dup2(bana->fd_output, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		shut_fd(fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	return (true);
}

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

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];

	if (!fork_it(bana, fd, &pid, index))
		return (false);
	if (pid == 0)
	{
		if (bana->cmd_paths[index])
			execve(bana->cmd_paths[index], &bana->cmd_args[index], envp); // ADDED &
		else
		{
			perror("Bananas!: Command not found");
			clean_n_errors(bana);
			//exit(1);
			return (1);
		}
	}
	else
		wait_it(bana, pid, index, fd);
	return (true);
}
