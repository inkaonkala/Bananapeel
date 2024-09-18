/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/18 10:05:02 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_tokens(char *str)
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
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				if (quotes && str[i] == current)
					quotes = 0;
				else if (!quotes)
				{
					quotes = 1;
					current = str[i];
				}
			}
			i++;
		}
	}
	return (count);
}

static bool	extract_tokens(char *str, char **tokens, t_bananas *bana)
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
			{
				free_char_array(tokens);
				return (false);
			}
			ft_strlcpy(tokens[token_i], &str[start], tok_len + 1);
			tokens[token_i] = dollar_check(tokens[token_i], bana->env, bana);
			if (!tokens[token_i])
			{
				free_char_array(tokens);
				return (false);
			}
			token_i++;
		}
	}
	return (true);
}

bool	parsing(char *str, t_bananas *bana)
{
	char	**tokens;
	int		token_count;

	token_count = count_tokens(str);
	if (token_count == 0)
		return (true);
	free_char_array(bana->envp);
	bana->envp = list_to_eepie(&bana->env);
	tokens = ft_calloc((token_count + 1), sizeof(char *));
	if (!tokens)
		return (false);
	if (!extract_tokens(str, tokens, bana))
	{
		free_char_array(tokens);
		return (false);
	}
	if (!banananice(bana, tokens, token_count))
		return (true);
	command_search(bana, bana->envp, &bana->env);
	return (true);
}
