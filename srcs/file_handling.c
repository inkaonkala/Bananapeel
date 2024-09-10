/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:06:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/10 13:48:45 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// make open_file.c

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

//
 
static char	*clean_arrows(char *str)
{
	int	i;
	int	j;
	char *copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if(!copy)
	{
		ft_printf("Malloc fail in arrows");
		return (NULL);
	}
	while(str[i] != '\0')
	{
		while(str[i] == '<' || str[i] == '>')
			i++;
		while(str[i] != '\0')
		{
			copy[j] = str[i];
			i++;
			j++;
		}
	}
	copy[j] = '\0';
	return (copy);
}

bool    file_handling(t_bananas *bana, int i)
{
    bool    append;

	if (ft_strncmp(bana->token[i], ">", 1) == 0)
	{		
		if (ft_strncmp(bana->token[i], ">>", 2) == 0)
		{
			append = true;

			if (ft_strncmp(bana->token[i], ">>\0", 3) != 0)
				bana->token[i] = clean_arrows(bana->token[i]);
			else
				token_cleaner(bana, i);
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			return (true);
		}	
		else if( ft_strncmp(bana->token[i], ">", 1) == 0)
		{
			append = false;
			if( ft_strncmp(bana->token[i], ">\0", 2) != 0)
				bana->token[i] = clean_arrows(bana->token[i]);
			else
				token_cleaner(bana, i);
			open_outfile(bana, i, append);
			token_cleaner(bana, i);
			return (true);
		}
		return (false);


	}
	if (ft_strncmp(bana->token[i], "<<", 2) == 0)
	{
		
		//if (ft_strncmp(bana->token[i], "<<\0", 3) != 0)
		bana->token[i] = clean_arrows(bana->token[i]);
		//else
		//	token_cleaner(bana, i);
		//return(true);
	}
	else if (ft_strncmp(bana->token[i], "<", 1) == 0)
	{
		if (ft_strncmp(bana->token[i], "<\0", 2) != 0)
			bana->token[i] = clean_arrows(bana->token[i]);
		else
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
