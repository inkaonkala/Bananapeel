/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 16:58:35 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_stuff(char **args, char *path)
{
	int	i;

	i = 0;
	while(args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	if (path)
		free(path);
}

void token_cleaner(t_bananas *bana, int i)
{
	free(bana->token[i]);
		while (i < bana->tok_num - 1)
		{
			// printf("incleaner\n");
			bana->token[i] = bana->token[i + 1];
			i++;	
		}
	bana->tok_num--;
	if (bana->tok_num == 0)
	{
	//	free(bana->token[0]);
		bana->token[0] = NULL;
	}
}

void    exiting(t_bananas *bana, int i)
{
	clean_struct(bana);
	exit(i);
}
    // If something else to clean, clean here mebbe?
