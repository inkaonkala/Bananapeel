/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:59:08 by iniska            #+#    #+#             */
/*   Updated: 2024/09/11 13:20:45 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	mallocing(t_bananas *bana, int in_file_count, int out_file_count)
{
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
}

void	file_malloc(t_bananas *bana)
{
	int	in_file_count;
	int	out_file_count;
	int	i;

	in_file_count = 0;
	out_file_count = 0;
	i = 0;
	while (i < bana->tok_num)
	{
		if (ft_strncmp(bana->token[i], "<", 1) == 0)
			in_file_count++;
		else if (ft_strncmp(bana->token[i], ">", 1) == 0
			|| ft_strncmp(bana->token[i], ">>", 2) == 0)
			out_file_count++;
		i++;
	}
	mallocing(bana, in_file_count, out_file_count);
	bana->infile_count = 0;
	bana->outfile_count = 0;
}
