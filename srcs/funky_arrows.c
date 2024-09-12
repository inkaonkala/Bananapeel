/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 14:13:28 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_files(t_bananas *bana)
{
	int i;

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

static void	dupper(t_bananas * bana)
{
	dprintf(2, "###### fds: in: %i, out: %i\n", bana->in_files[bana->infile_count - 1], bana->out_files[bana->outfile_count - 1]);
	if (bana->infile_count > 0)
	{
		if (dup2(bana->in_files[bana->infile_count - 1], STDIN_FILENO) < 0)
			cleanup_and_exit(bana, -1);
			
	}
	if(bana->outfile_count > 0)
	{
	
		if (dup2(bana->out_files[bana->outfile_count - 1], STDOUT_FILENO) < 0)
		{
			perror("Bananas! Error in dup2 PUTPUT redirections\n");
			cleanup_and_exit(bana, -1);
		}
	}
}

static void	execute_rdr(t_bananas *bana, char **envp, t_node **env)
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
		dprintf(2, "##builtin: in: %i, out: %i\n", bana->in_files[bana->infile_count - 1], bana->out_files[bana->outfile_count - 1]);
		dupper(bana);
		close_files(bana);
		cmd_args = ft_split(bana->token[0], ' ');
		if(cmd_args == NULL)
		{
			ft_printf("Bnanas! Failed to split the command arguments\n");
			free_stuff(cmd_args, path);
			cleanup_and_exit(bana, 1);
		}
		path = get_path(cmd_args[0], envp);
		if(!path)
		{
			printf("%s: command not found\n", cmd_args[0]);
			free_stuff(cmd_args, NULL);
			cleanup_and_exit(bana, 127);
		}
		built_ins(bana, env);
		token_cleaner(bana, 0);
		execve(path, cmd_args, envp);
		perror("execve");
		free_stuff(cmd_args, path);
		cleanup_and_exit(bana, 126);
	}
	else
	{
		waitpid(pid, &status, 0);
		bana->last_exit_status = WEXITSTATUS(status);
	}
}


void    redirections(t_bananas *bana, char **envp, t_node **env)
{
	if (bana->tok_num < 2)
	{
		clean_struct(bana);
		return ;
	}
	file_handling(bana);
	if(bana->is_dog && bana->tok_num < 1)
	{
		clean_struct(bana);
		return ;
	}
	if(!bana->is_pipe)
	{
		execute_rdr(bana, envp, env);
		while(bana->tok_num > 0)
			token_cleaner(bana, 0);
	}
}
