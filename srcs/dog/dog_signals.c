/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dog_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:10:41 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 15:30:47 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*readline_wrapper(const char *prompt, t_bananas *bana)
{
	char	*line;

	line = readline(prompt);
	if (big_stopping(GET, 0))
	{
		free(line);
		bana->heredog_interrupted = 1;
		return (NULL);
	}
	return (line);
}

int	big_stopping(int get, int newvalue)
{
	static int	stopper = 0;

	if (get)
		return (stopper);
	else
		stopper = newvalue;
	return (stopper);
}
