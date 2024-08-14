/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:06:52 by iniska            #+#    #+#             */
/*   Updated: 2024/08/13 15:11:00 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    open_infile(t_bananas *bana, int i)
{
	int	fd;

	ft_printf("Opening input file: %s\n", bana->token[i]);

	fd = open(bana->token[i], O_RDONLY);
	if (fd == -1)
	{
		//fd = open(bana->token[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		//ft_printf("opened an infile\n");
		if(fd == -1)
		{
			ft_printf("%s: ", bana->token[i]);
			perror("Bananas!");
			return ;
		}
	}
	bana->in_files[bana->infile_count] = fd;
	bana->infile_count++;
}

static void    open_outfile(t_bananas *bana, int i, bool append)
{
	int	fd;
	
	ft_printf("Opening output file: %s\n", bana->token[i]);
	
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

void    file_handling(t_bananas *bana, int i)
{
    bool    append;

    // find > ar >> for outfiles
	if ((ft_strncmp(bana->token[i], ">>", 2) == 0) || (ft_strncmp(bana->token[i], ">", 1) == 0))
	{
		if (ft_strncmp(bana->token[i], ">>\0", 3) == 0)
		{
			append = true;
			token_cleaner(bana, i);
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
		}	
		else if( ft_strncmp(bana->token[i], ">\0", 2) == 0)
		{
			append = false;
			token_cleaner(bana, i);
			// take the token token[>] and delete it, incrament file to this spot and token_count--
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
		}

	}
	// find < for infiles
	if (ft_strncmp(bana->token[i], "<\0", 2) == 0)
	{
		token_cleaner(bana, i);
		open_infile(bana, i);
		token_cleaner(bana, i);
	}
	else
		return ;
}

void    file_malloc(t_bananas *bana) // THIS MALLOC NEEDS TO BE CORRECTED?
{
    //somehow we should count the amount of actual files for right mallocsize
    bana->in_files = malloc(sizeof(int) * bana->tok_num);
	if(!bana->in_files)
	{
		perror("Mallocin in_files failed\n");
		return ;
	}
    bana->out_files = malloc(sizeof(int) * bana->tok_num);
	if (!bana->out_files)
	{
		perror("Mallocin out_files failed\n");
		free(bana->in_files);
		return ;
	}

}