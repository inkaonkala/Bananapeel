/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:01:29 by iniska            #+#    #+#             */
/*   Updated: 2024/09/17 09:43:56 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_infile(t_bananas *bana, int i)
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
			ft_printf("Bananas! : Unable to find heredog delimiter\n");
		set_heredog_status(OUT_HEREDOG);
		bana->is_dog = true;
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
		ft_printf("Bananas! Unexpected token while in heredog: %s\n", bana->token[i]);
		return ;
	}
	bana->infile_count++;
}

void	open_outfile(t_bananas *bana, int i, bool append)
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
