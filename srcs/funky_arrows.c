/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funky_arrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:37 by iniska            #+#    #+#             */
/*   Updated: 2024/08/08 10:29:55 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// REDIRECTION!


void    redirections(t_bananas *bana)
{
	int		i;
	
	i = 0;
	while(bana->token[i])
	{
		file_malloc(bana);
		file_handling(bana, i);
		i++;
	}
}

