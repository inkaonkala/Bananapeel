/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 16:56:38 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void empty_prompt(void)
{
    char *line;
    int fd[2];

    signal(SIGINT, handle_sigint_s);
    if (pipe(fd) == -1) {
        perror("Bananas! Pipe creation failed");
        return;
    }
    line = readline("");
	while (line)
    {
        ft_putendl_fd(line, fd[1]);
        free(line);
        line = readline("");
    }
    close(fd[1]);
    signal(SIGINT, SIG_DFL);
}

static void	execute_command(t_bananas *bana, char **envp, int index)
{
	char **cmd_args;

	cmd_args = ft_split(bana->token[index], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		ft_printf("Bananas! Failed to split command arguments\n");
		exiting(bana, 1);
	}
	if (!ft_strncmp(cmd_args[0], "exit", 5))
	{
		handle_exit(bana);
		free(cmd_args);
		exiting(bana, 0);
	}
	if(bana->cmd_paths[index])
	{
			execve(bana->cmd_paths[index], cmd_args, envp);
			ft_printf("Bananas! Failed to execute command: %s\n", strerror(errno));
			free_argh(cmd_args);
			exiting(bana, 126);
	}
	else
	{
		ft_printf("Bananas! Can't find your command :( \n");
		free_argh(cmd_args);
		exiting(bana, 127);
	}
	free_argh(cmd_args);
	exiting(bana, 1);
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

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;
	int		status;

	last = (index == bana->tok_num) -1;

	if (!fork_it(bana, fd, &pid, index))
		return (false);
	if (pid == 0)
	{
		if(bana->is_rdr)
		{
			if(!redirect_file_input(bana))
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

