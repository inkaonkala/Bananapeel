/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:04:29 by iniska            #+#    #+#             */
/*   Updated: 2024/08/20 14:09:38 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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

static int	get_infile(t_bananas *bana)
{
	int fd;

	// Assuming the infile is the second token for now !!!
	if (bana->tok_num < 2 || bana->token[1] == NULL)
	{
		perror("Bananas! No input file givency\n");
		return (-1);
	}
	printf("Opening input file: %s\n", bana->token[1]);
	fd = open(bana->token[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Bananas!: Error opening input file");
		return (-1);
	}
	bana->fd_input = fd;
	return (bana->fd_input);
}

static int	get_outfile(t_bananas *bana)
{
	// Assuming the outfile is the last token for now !!!
	if (bana->tok_num < 2 || bana->token[bana->tok_num - 1] == NULL)
	{
		perror("Bananas! Flawed output\n");
		return (-1);
	}
	printf("Opening output file: %s\n", bana->token[bana->tok_num - 1]);
	bana->fd_output = open(bana->token[bana->tok_num - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (bana->fd_output == -1)
	{
		perror("Bananas!: Error opening output file");
		//exit(1);
		return (1);
	}
	return (bana->fd_output);
}

bool	check_arguments(t_bananas *bana)
{	
	if (get_infile(bana) == -1)
	{
		perror("Bananas!: Infile does not work\n");
		return (false);
	}
	if (get_outfile(bana) == -1)
	{
		perror("Bananas!: Bad arguments! \n");
		return (false);
	}
	return (true);
}
