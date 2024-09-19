/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 10:53:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	do_it(t_bananas *bana, char **envp, int index, char **cmd_args)
{
	execve(bana->cmd_paths[index], cmd_args, envp);
	ft_printf("Bananas! Failed to execute command: %s\n", strerror(errno));
	free_argh(cmd_args);
	exiting(bana, 126);
}

void	execute_command(t_bananas *bana, char **envp, int index)
{
	char	**cmd_args;

	cmd_args = ft_split(bana->token[index], ' ');
	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		printf("Bananas! Failed to split command arguments\n");
		exiting(bana, 1);
	}
	if (!ft_strncmp(cmd_args[0], "exit", 5))
	{
		handle_exit(bana);
		free(cmd_args);
		exiting(bana, 0);
	}
	if (bana->cmd_paths[index])
		do_it(bana, envp, index, cmd_args);
	else
	{
		printf("Command is bananas! \n");
		free_argh(cmd_args);
		clean_struct(bana);
		exiting(bana, 127);
	}
	free_argh(cmd_args);
	exiting(bana, 1);
}
