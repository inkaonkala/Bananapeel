/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/20 10:55:16 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*clean_deli(char *str)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * 4);
	if (!copy)
	{
		ft_printf("Malloc fail in dog\n");
		return (0);
	}
	while (str[i] == '<' && str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	find_dog(t_bananas *bana, int tk_i)
{
	char	*delimiter;
	char	separate;

	separate = 0;
	if (ft_strlen(bana->token[tk_i]) == 2)
	{
		delimiter = find_delimiter(bana);
		separate = 1;
	}
	else
	{
		delimiter = bana->token[tk_i] + 2;
		bana->token[tk_i] = clean_deli(bana->token[tk_i]);
	}
	handle_the_dog(delimiter, bana);
	if (separate)
		free(delimiter);
}
