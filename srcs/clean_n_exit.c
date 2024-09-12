/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/11 12:56:16 by iniska           ###   ########.fr       */
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
    // If something else to clean, clean here mebbe?
	if (i == 0)
		exit (0);
	if (i == 1)
		exit (-1);
}
