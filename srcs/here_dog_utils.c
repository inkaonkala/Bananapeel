/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:25:20 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/12 10:33:21 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline char	*_getstatus(void)
{
	static char	status = 0;

	return (&status);
}

char    get_heredog_status(void)
{
		return (*_getstatus());
}


void    set_heredog_status(char status)
{
	*_getstatus() = status;
}
