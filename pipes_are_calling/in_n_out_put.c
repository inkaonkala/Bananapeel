/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_n_out_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:30:36 by iniska            #+#    #+#             */
/*   Updated: 2024/08/21 10:32:41 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	redirect_input(t_bananas *bana, int index)
{
		if (index == 0 && bana->fd_input != -1)
		{
			dup2(bana->fd_input, STDIN_FILENO);
			close(bana->fd_input);
		}
		else if (index > 0)
		{
			dup2(bana->prev_fd[0], STDIN_FILENO);
			close(bana->prev_fd[0]);
		}
}

void	redirect_putput(t_bananas *bana, int fd[2], int index)
{
	if (index == bana->tok_num && bana->fd_output != -1)
	{
		
		dup2(bana->fd_output, STDOUT_FILENO);
		close(bana->fd_output);
	}
	else if(index < bana->tok_num - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		shut_fd(fd);
	}
}

bool	redirect_file_input(t_bananas *bana)
{
	int	fd;

	if( bana->infile_count > 0)
	{
		fd = bana->in_files[0];
	
		if (fd != -1)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Failed to redirect input to file\n");
				exit(EXIT_FAILURE);
			}
			close(fd);
			return (true);
		}
	}
	return (false);
	
}

void	redirect_file_putput(t_bananas *bana)
{
	int	fd;

	if(bana->outfile_count > 0)
	{
		fd = bana->out_files[bana->outfile_count - 1]; // HERE IS THE PROBLEM
		
		if(fd != -1)
		{
			if(dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Failed to redirect output to file");
				exit(EXIT_FAILURE);
			}
			close(fd);
		}
	}
}


