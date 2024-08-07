/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/08/07 14:17:51 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    open_infile(t_bananas *bana, int i)
{
	int	fd;

	//what if no file and need to create one?
    ft_printf("Opening input file: %s\n", bana->token[i]);

	fd = open(bana->token[i], O_RDONLY);
	if (fd == -1)
	{
		perror("Bananas!: Error opening input file");
		return ;
	}
	bana->in_files[bana->infile_count] = fd;
	bana->infile_count++;
}

static void    open_outfile(t_bananas *bana, int i, bool append)
{
	int	fd;
	
	ft_printf("open_outfile");
	
	if (append)
		fd = open(bana->token[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(bana->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);

	if (fd == -1)
	{
		perror("Bananas!: Error opening output file");
		return ;
	}
	bana->out_files[bana->outfile_count] = fd;
	bana->outfile_count++;

}

void    redirections(t_bananas *bana)
{
	int		i;
	bool	append;

	i = 0;
	while(bana->token[i])
	{
    // find > ar >> for outfiles
		if (ft_strncmp(bana->token[i], ">>", 2) == 0)
		{
			append = true;
			token_cleaner(bana, i);
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			continue ;
		}
		
		if( ft_strncmp(bana->token[i], ">", 1) == 0)
		{
			append = false;
			token_cleaner(bana, i);
			// take the token token[>] and delete it, incrament file to this spot and token_count--
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			continue ;
		}
		// find < for infiles
		if (ft_strncmp(bana->token[i], "<", 1) == 0)
		{
			token_cleaner(bana, i);
			open_infile(bana, i);
			token_cleaner(bana, i);
			continue ;
		}
		i++;
	}
    
}


/*
// FILE HANDELING FROM PIPEX FOR HELP:
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

*/
