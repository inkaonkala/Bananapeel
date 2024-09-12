/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/09/11 14:42:41 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
// this is here for the lonely cat
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
*/

static void	execute_command(t_bananas *bana, char **envp, int index)
{
	char	**cmd_args;

	cmd_args = ft_split(bana->token[index], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		ft_printf("Bananas! Failed to split command arguments\n");
		exiting(bana, 1);
	}
	if (bana->cmd_paths[index])
	{
		execve(bana->cmd_paths[index], cmd_args, envp);
		exiting(bana, 1);
	}
	else
	{
		ft_printf("Bananas! Can't find your command :( \n");
		exiting(bana, 0);
	}
	free_argh(cmd_args);
}

bool	fork_it(t_bananas *bana, int fd[2], pid_t *pid, int index)
{
	if (index < bana->tok_num)
	{
		if (pipe(fd) == -1)
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

static void	pid_is_more(t_bananas *bana, int index, int last, int fd[2])
{
	if (index > 0)
		close(bana->prev_fd[0]);
	if (!last)
	{
		bana->prev_fd[0] = fd[0];
		close(fd[1]);
	}
	else
		shut_fd(fd);
}

static void	file_put(t_bananas *bana, int index, int fd[2])
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
		file_put(bana, index, fd);
		execute_command(bana, envp, index);
		exit (1);
	}
	else
		pid_is_more(bana, index, last, fd);
	return (true);
}
