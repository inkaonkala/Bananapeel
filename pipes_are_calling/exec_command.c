/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/09/27 13:20:24 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_path(t_bananas *bana)
{
	int	b;

	b = 0;
	if (bana->cmd_paths != NULL)
	{
		while (bana->cmd_paths[b] != NULL)
		{
			free(bana->cmd_paths[b]);
			b++;
		}
		free(bana->cmd_paths);
		bana->cmd_paths = NULL;
	}
}

static void	cleanup(t_bananas *bana, char **cmd_args)
{
	printf("Command is bananas! \n");
	free_path(bana);
	free_argh(cmd_args);
	exiting(bana, 127);
}

static void	close_unused_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < FD_MAX)
	{
		close(fd);
		fd++;
	}
}

static void	do_it(t_bananas *bana, char **envp, int index, char **cmd_args)
{
	close_unused_fds();
	execve(bana->cmd_paths[index], cmd_args, envp);
	ft_printf("Bananas! Failed to execute command: %s\n", strerror(errno));
	free_argh(cmd_args);
	clean_struct(bana);
	exiting(bana, 126);
}

void	execute_command(t_bananas *bana, char **envp, int index)
{
	char	**cmd_args;

	cmd_args = ft_split(bana->token[index], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		printf("Bananas! Failed to split command arguments\n");
		free_argh(cmd_args);
		exiting(bana, 1);
	}
	if (!ft_strncmp(cmd_args[0], "exit", 5))
	{
		free_argh(cmd_args);
		handle_exit(bana);
		exiting(bana, 0);
	}
	if (bana->cmd_paths[index])
		do_it(bana, envp, index, cmd_args);
	else
		cleanup(bana, cmd_args);
	free_argh(cmd_args);
	exiting(bana, 1);
}
