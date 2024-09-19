/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:07:07 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 16:20:23 by jbremser         ###   ########.fr       */
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
	free_env(&bana->env);
	free_char_array(bana->envp);
}

bool	return_n_free(char **tokens)
{
	free_char_array(tokens);
	return (false);
}
