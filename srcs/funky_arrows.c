/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/08/14 09:03:42 by iniska           ###   ########.fr       */
/*   Updated: 2024/08/09 11:54:00 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// REDIRECTION!

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

static void	execute_rdr(t_bananas *bana, char **envp)
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
		if (bana->infile_count > 0)
		{
			if (dup2(bana->in_files[bana->infile_count - 1], STDIN_FILENO) < 0) // SHOULD THIS -1 BE REMOVED
			{
				perror("Bananas! Error in dup2 for INPUT redirection\n");
				exit(EXIT_FAILURE); //CHECK THIS!
			}
		}
		
		if(bana->outfile_count > 0)
		{
			if (dup2(bana->out_files[bana->outfile_count - 1], STDOUT_FILENO) < 0)
			{
				perror("Bananas! Error in dup2 PUTPUT redirections\n");
				exit(EXIT_FAILURE);
			}
		}
		
		close_files(bana);
		ft_printf("Gonna look for PATH\n");
		path = get_path(bana->token[0], envp);
		ft_printf("			PATH:: %s\n", path);
		if(!path)
		{
			perror("Command is bananas:");
			exit(EXIT_FAILURE);
		}
		ft_printf("		before EXECV\n");
		execve(path, bana->token, envp);
		free(path);


		//perror("Bananas! Error in rdr execve");
	}
	else
		waitpid(pid, &status, 0);		
}

void    redirections(t_bananas *bana, char **envp)
{
	int		i;
	
	i = 0;
	while(bana->token[i])
	{
		file_malloc(bana);
		file_handling(bana, i);
		i++;
	}
	if(!bana->is_pipe)
	{
		execute_rdr(bana, envp);
		token_cleaner(bana, 0);
	}

}
