/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/08/16 10:23:22 by iniska           ###   ########.fr       */
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

	
	ft_printf("			the set FD DUP DUP DUP 1 	%d\n", bana->out_files[bana->outfile_count - 1]);

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
		
		ft_printf("%d\n \n", bana->outfile_count);
		ft_printf("		FD NUMBER = %d\n", bana->out_files[bana->outfile_count - 1]);
		
		
		if(bana->outfile_count > 0)
		{
			ft_printf(" :::::::::::::::: DUPPING! :::::::::::::::::::\n");
			ft_printf("		FD NUMBER IN DUP = %d\n", bana->out_files[bana->outfile_count - 1]);
			
			if (dup2(bana->out_files[bana->outfile_count - 1], STDOUT_FILENO) < 0)
			{
				perror("Bananas! Error in dup2 PUTPUT redirections\n");
				exit(EXIT_FAILURE);
			}
		}
		
		close_files(bana);
		path = get_path(bana->token[0], envp);		
		if(!path)
		{
			perror("Command is bananas:");
			exit(EXIT_FAILURE);
		}
		
		token_cleaner(bana, 0);

		execve(path, bana->token, envp);
		free(path);
	}
	else
		waitpid(pid, &status, 0);		
}

void    redirections(t_bananas *bana, char **envp)
{
	// this is not incramenting right and it delets the fd!
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
		ft_printf("			the set REDIRDIER 1 	%d\n", bana->out_files[bana->outfile_count - 1]);
		i++;
	}
	if(!bana->is_pipe)
	{
		execute_rdr(bana, envp);
		//token_cleaner(bana, 0);
	}

}
