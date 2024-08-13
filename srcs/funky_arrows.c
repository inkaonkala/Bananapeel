/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
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
			if (dup2(bana->in_files[bana->infile_count - 1], STDOUT_FILENO) < 0)
			{
				perror("Bananas! Error in dup2 for output redirection");
				exit(EXIT_FAILURE); //CHECK THIS!
			}
		}
		close_files(bana);
		ft_printf("%s\n", bana->token[0]);
		execve(bana->token[0], bana->token, envp);
		envp = NULL;
		token_cleaner(bana, 0);
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
		execute_rdr(bana, envp);
}
