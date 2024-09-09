/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/09/09 11:34:49 by iniska           ###   ########.fr       */
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
	if (bana->infile_count > 0)
	{
		if (dup2(bana->in_files[bana->infile_count - 1], STDIN_FILENO) < 0)
			exiting(bana, -1);
			
	}
	if(bana->outfile_count > 0)
	{
	
		if (dup2(bana->out_files[bana->outfile_count - 1], STDOUT_FILENO) < 0)
		{
			perror("Bananas! Error in dup2 PUTPUT redirections\n");
			exiting(bana, -1);
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

		dupper(bana);
		close_files(bana);
	
		cmd_args = ft_split(bana->token[0], ' ');
		if(cmd_args == NULL)
		{
			ft_printf("Bnanas! Failed to split the command arguments\n");
			free_stuff(cmd_args, path);
			exiting(bana, 1);
		}
		path = get_path(cmd_args[0], envp);		
		if(!path)
		{
			printf("%s\n", cmd_args[0]);
			built_ins(bana, env);
			perror("Command is bananas:");
			free_stuff(cmd_args, NULL);
			exit(EXIT_FAILURE);
		}
		built_ins(bana, env);
		token_cleaner(bana, 0);
		execve(path, cmd_args, envp);
		free_stuff(cmd_args, path);
		exiting(bana, -1);
	}
	else
		waitpid(pid, &status, 0);
}

void    redirections(t_bananas *bana, char **envp, t_node **env)
{
	int		i;
	
	i = 0;
	while(bana->token[i])
	{
		//file_malloc(bana);
		if(file_handling(bana, i))
			continue ;
		i++;
	}
	if(!bana->is_pipe)
	{
		execute_rdr(bana, envp, env);
		while(bana->tok_num > 0)
			token_cleaner(bana, 0);
	}
	//FREE SOMETHING? exiting(bana, 1);
}
