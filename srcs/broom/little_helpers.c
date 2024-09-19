/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 11:37:10 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	empties(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	quote_chk(char *str, char *cur_quo, int i)
{
	int	quotes;

	quotes = 0;
	while (str[i] && (!empties(str[i]) || quotes))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (quotes && str[i] == *cur_quo)
				quotes = 0;
			else if (!quotes)
			{
				quotes = 1;
				*cur_quo = str[i];
			}
		}
		i++;
	}
	return (i);
}

bool	check_specials(char *token)
{
	if (ft_strcmp(token, "|") == 0
		|| ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0)
		return (true);
	return (false);
}

int	number_checker(char *argv)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(argv) - 1)
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
