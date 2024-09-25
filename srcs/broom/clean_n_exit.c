/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/25 14:30:32 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exiting(t_bananas *bana, int i)
{
	clean_banana(bana);
	exit(i);
}

void	clean_banana(t_bananas *bana)
{
	clean_struct(bana);
	if(bana->env)
	{
		dprintf(2, "herre\n");
		free_env(&bana->env);
		if (bana->envp[0])
		{
			dprintf(2, "dsadsa\n");
			free_char_array(bana->envp);
		}
	}
}

bool	return_n_free(char **tokens)
{
	free_char_array(tokens);
	return (false);
}
