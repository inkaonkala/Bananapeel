/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 13:02:10 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void token_cleaner(t_bananas *bana, int i)
{
	free(bana->token[i]);
		while (i < bana->tok_num - 1)
		{
			bana->token[i] = bana->token[i + 1];
			i++;	
		}
	bana->tok_num--;
	if (bana->tok_num == 0)
		bana->token[0] = NULL;
}

void    cleanup_and_exit(t_bananas *bana, int status)
{
	clean_struct(bana);
	exit (status);
}
