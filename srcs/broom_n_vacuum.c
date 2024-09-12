/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broom_n_vacuum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:23:36 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 10:24:46 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void clean_files(t_bananas *bana)
{
	if (bana->in_files != NULL)
	{
		free(bana->in_files);
		bana->in_files = NULL;
	}

	if(bana->out_files != NULL)
	{
		free(bana->out_files);
		bana->out_files = NULL;
	}
}


void	clean_struct(t_bananas *bana)
{
	if (bana->tok_num > 0)
		token_cleaner(bana, 0);

	clean_files(bana);
	if(bana->pipes != NULL)
	{
		free(bana->pipes);
		bana->pipes = NULL;
	}
	bana->tok_num = 0;
	bana->infile_count = 0;
	bana->outfile_count = 0;
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;

}