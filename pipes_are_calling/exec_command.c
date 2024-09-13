/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/09/13 10:45:52 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_command(t_bananas *bana, char **envp, int index)
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
