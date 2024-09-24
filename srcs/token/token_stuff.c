/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:51:19 by iniska            #+#    #+#             */
/*   Updated: 2024/09/23 14:51:45 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	quoter(char *str, int i, int *quotes, char *current)
{
	if (str[i] == '"' || str[i] == '\'')
	{
		if (*quotes && str[i] == *current)
			*quotes = 0;
		else if (!(*quotes))
		{
			*quotes = 1;
			*current = str[i];
		}
	}
	return (i + 1);
}

int	count_tokens(char *str)
{
	int		count;
	int		i;
	int		quotes;
	char	current;

	i = 0;
	count = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && empties(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && (!empties(str[i]) || quotes))
			i = quoter(str, i, &quotes, &current);
	}
	return (count);
}

/*
int i[0] = an iterator for string
int i[1] = an iterator for tokens
int i[2] = the point in the array that we will start a new token
int i[3] = the token length
*/

bool	extract_tokens(char *str, char **tokens, t_bananas *bana)
{
	int		i[4];
	char	cur_quo;

	i[0] = 0;
	i[1] = 0;
	cur_quo = 0;
	while (str[i[0]])
	{
		while (str[i[0]] && empties(str[i[0]]))
			i[0]++;
		if (str[i[0]])
		{
			i[2] = i[0];
			i[0] = quote_chk(str, &cur_quo, i[0]);
			i[3] = i[0] - i[2];
			tokens[i[1]] = malloc(i[3] + 1);
			if (!tokens[i[1]])
				return (return_n_free(tokens));
			ft_strlcpy(tokens[i[1]], &str[i[2]], i[3] + 1);
			tokens[i[1]] = dollar_check(tokens[i[1]], bana->env, bana);
			if (!tokens[i[1]++])
				return (return_n_free(tokens));
		}
	}
	return (true);
}
