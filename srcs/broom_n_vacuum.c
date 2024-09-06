/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broom_n_vacuum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:23:36 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 14:46:17 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void clean_files(t_bananas *bana)
{
	// int i; 
	
	// i = 0;

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
	
/*
	this CRASHes if execve fails
	
	if(bana->cmd_paths != NULL)
	{
		while(bana->cmd_paths[i] != NULL)
		{
			free(bana->cmd_paths[i]);
			bana->cmd_paths[i] = NULL;
			i++;
		}
		free(bana->cmd_paths);
		bana->cmd_paths = NULL;
	}
*/	
}


void	clean_struct(t_bananas *bana)
{
	//printf("PATH: %s\n", bana->cmd_paths[0]);

	if (bana->tok_num > 0)
		token_cleaner(bana, 0);

	clean_files(bana);
	if(bana->pipes != NULL)
	{
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