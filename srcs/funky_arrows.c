/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/08/26 14:36:45 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

/*
static void	if_echo(t_bananas *bana, int i)
{
	if(strcmp(bana->token[0], "echo") == 0)
	{
		int i;
		bool n_flag;

		n_flag = false;
		i = 1;

		if (bana->tok_num == 1)
			printf("\n");
		else if (bana->tok_num > 1)
		{
			if (ft_strcmp(bana->token[1], "-n") == 0)
			{
				token_cleaner(bana, 1);
				n_flag = true;
			}
			while (i <= bana->tok_num - 2)
				printf("%s ", bana->token[i++]);
			if (bana->tok_num >= 2)
				printf("%s", bana->token[bana->tok_num - 1]);
			if (n_flag == false)
				printf("\n");
		}
		while (bana->tok_num > 0)
			token_cleaner(bana, 0);
		exit (0);
	}
}
*/

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
		path = get_path(bana->token[0], envp);		
		if(!path)
		{
			built_ins(bana, env);
			perror("Command is bananas:"); THIS SHOULD BE PRINTE IF THERE IS NO BUILT_INS COMMAND
			exit(EXIT_FAILURE);
		}
		//if_echo(bana);
		built_ins(bana, env);
		token_cleaner(bana, 0);
		execve(path, bana->token, envp);
		exiting(bana, -1);
	}
	//free(path);
	else
		waitpid(pid, &status, 0);		
}

void    redirections(t_bananas *bana, char **envp, t_node **env)
{
	int		i;
	
	i = 0;
	bana->outfile_count = 0;
	bana->infile_count = 0;
	file_malloc(bana);
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
