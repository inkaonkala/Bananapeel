/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:06:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 12:01:32 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void    open_infile(t_bananas *bana, int i)
{
	int	fd;

	if (ft_strncmp(bana->token[i], "<<", 2) == 0)
	{
		set_heredog_status(IN_HEREDOG);
		char *delimiter = find_delimiter(bana);
		if (delimiter)
		{
			handle_the_dog(delimiter, bana);
			free(delimiter);
		}
		else
			ft_printf("Error: Unable to find heredog delimiter\n");
		set_heredog_status(OUT_HEREDOG);
		bana->is_dog = true;
		//ft_printf("FD should be the heredog pipe\n");
	}
	else if (get_heredog_status() == OUT_HEREDOG)
	{
		fd = open(bana->token[i], O_RDONLY);
		if (fd == -1)
		{
			//ft_printf("%s: ", bana->token[i]);
			perror("Bananas!");
			return ;
		}
		bana->in_files[bana->infile_count] = fd;
	}
	else
	{
		ft_printf("Unexpected token while in heredog: %s\n", bana->token[i]);
		return ;
	}
	bana->infile_count++;
}

static void    open_outfile(t_bananas *bana, int i, bool append)
{
	int	fd;

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

bool    file_handling(t_bananas *bana, int i)
{
    bool    append;

	if ((ft_strncmp(bana->token[i], ">>", 2) == 0) || (ft_strncmp(bana->token[i], ">", 1) == 0))
	{
		if (ft_strncmp(bana->token[i], ">>\0", 3) == 0)
		{
			append = true;
			token_cleaner(bana, i);
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			return (true);
		}	
		else if( ft_strncmp(bana->token[i], ">\0", 2) == 0)
		{
			append = false;
			token_cleaner(bana, i);
			// take the token token[>] and delete it, incrament file to this spot and token_count--
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			return (true);
		}
		return (false);


	}
	if (ft_strncmp(bana->token[i], "<\0", 2) == 0)
	{
		token_cleaner(bana, i);
		open_infile(bana, i);
		token_cleaner(bana, i);
		return (true);
	}
	
	return (false);
}

void file_malloc(t_bananas *bana)
{
    int in_file_count;
    int out_file_count;
    int i;

	in_file_count = 0;
	out_file_count = 0;
	i = 0;
    while (i < bana->tok_num)
    {
        if (ft_strncmp(bana->token[i], "<", 1) == 0)
            in_file_count++;
        else if (ft_strncmp(bana->token[i], ">", 1) == 0 || ft_strncmp(bana->token[i], ">>", 2) == 0)
            out_file_count++;
        i++;
    }
    bana->in_files = malloc(sizeof(int) * in_file_count);
    if (!bana->in_files)
    {
        perror("Malloc in_files failed");
        return ;
    }
    bana->out_files = malloc(sizeof(int) * out_file_count);
    if (!bana->out_files)
    {
        perror("Malloc out_files failed");
        free(bana->in_files);
        return ;
    }
    bana->infile_count = 0;
    bana->outfile_count = 0;
}
