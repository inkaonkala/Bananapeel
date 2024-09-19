/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:51:19 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 12:39:46 by iniska           ###   ########.fr       */
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

bool	extract_tokens(char *str, char **tokens, t_bananas *bana)
{
	int		i;
	int		token_i;
	int		start;
	char	cur_quo;
	int		tok_len;

	i = 0;
	token_i = 0;
	cur_quo = 0;
	while (str[i])
	{
		while (str[i] && empties(str[i]))
			i++;
		if (str[i])
		{
			start = i;
			i = quote_chk(str, &cur_quo, i);
			tok_len = i - start;
			tokens[token_i] = malloc(tok_len + 1);
			if (!tokens[token_i])
				return (return_n_free(tokens));
			ft_strlcpy(tokens[token_i], &str[start], tok_len + 1);
			tokens[token_i] = dollar_check(tokens[token_i], bana->env, bana);
			if (!tokens[token_i])
				return (return_n_free(tokens));
			token_i++;
		}
	}
	return (true);
}
