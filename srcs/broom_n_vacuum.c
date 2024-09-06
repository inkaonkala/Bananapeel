/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broom_n_vacuum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:23:36 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 10:25:24 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_struct(t_bananas *bana)
{
	//printf("PATH: %s\n", bana->cmd_paths[0]);
	
	int i;
	
	i = 0;
	if (bana->tok_num > 0)
	{
		token_cleaner(bana, 0); // WRITE A NEW CLEANING FUNCTION?
	}

	if (bana->in_files != NULL)
	{
	//	printf("\n infile nulled\n");
		free(bana->in_files);
		bana->in_files = NULL;
	}

	if(bana->out_files != NULL)
	{
	//	printf("\noutfiles nulled \n");
		free(bana->out_files);
		bana->out_files = NULL;
	}

	if(bana->cmd_paths != NULL)
	{
		i = 0;
		while(bana->cmd_paths[i] != NULL)
		{
			free(bana->cmd_paths[i]);
			bana->cmd_paths[i] = NULL;
			i++;
		}
		free(bana->cmd_paths);
		bana->cmd_paths = NULL;
	}

	if(bana->pipes != NULL)
	{
	//	printf("\n pipes freed\n");
		free(bana->pipes);
		bana->pipes = NULL;
	}

	// RESETER
	bana->tok_num = 0;
	bana->infile_count = 0;
	bana->outfile_count = 0;
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
	
}