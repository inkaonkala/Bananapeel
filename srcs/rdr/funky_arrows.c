/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/09/25 13:59:02 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	close_files(t_bananas *bana)
{
	int	i;

	i = 0;
	while (i < bana->infile_count)
	{
		close(bana->in_files[i]);
		i++;
	}
	i = 0;
	while (i < bana-> outfile_count)
	{
		close(bana->out_files[i]);
		i++;
	}
}

static void	dupper(t_bananas *bana)
{
	if (bana->infile_count > 0)
	{
		if (dup2(bana->in_files[bana->infile_count - 1], STDIN_FILENO) < 0)
			exiting(bana, -1);
	}
	if (bana->outfile_count > 0)
	{
		if (dup2(bana->out_files[bana->outfile_count - 1], STDOUT_FILENO) < 0)
		{
			perror("Bananas! Error in dup2 PUTPUT redirections\n");
			exiting(bana, -1);
		}
	}
}

static void	last_pipe(t_bananas *bana, char **envp)
{
	char	*path;
	char	**cmd_args;

	path = NULL;
	cmd_args = ft_split(bana->token[0], ' ');
	if (cmd_args == NULL)
	{
		ft_printf("Bnanas! Failed to split the command arguments\n");
		free_stuff(cmd_args, path);
		exiting(bana, 1);
	}
	path = get_path(cmd_args[0], envp);
	if (!path)
	{
		printf("%s\n", cmd_args[0]);
		built_ins(bana);
		perror("Command is bananas:");
		free_stuff(cmd_args, NULL);
		exiting(bana, 126);
	}
	built_ins(bana);
	token_cleaner(bana, 0);
	execve(path, cmd_args, envp);
	free_stuff(cmd_args, path);
	exiting(bana, -1);
}

static void	execute_rdr(t_bananas *bana, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**cmd_args;

	cmd_args = NULL;
	path = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("Bananas not forking");
		return ;
	}
	if (pid == 0)
	{
		dupper(bana);
		close_files(bana);
		last_pipe(bana, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		bana->last_exit_status = WEXITSTATUS(status);
	}
}

void	redirections(t_bananas *bana, char **envp)
{
	if (bana->tok_num < 2)
	{
		clean_struct(bana);
		return ;
	}
	file_handling(bana);
	if (bana->is_dog && bana->tok_num < 1)
	{
		clean_struct(bana);
		return ;
	}
	if (!bana->is_pipe || bana->rdr_in_pipe)
	{
		execute_rdr(bana, envp);
		if (bana->rdr_in_pipe)
			return ;
		clean_struct(bana);
	}
}
