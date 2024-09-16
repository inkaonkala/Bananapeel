/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/16 13:46:22 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**list_to_eepie(t_node **env) //claudes
{
	int		len;
	int		i;
	t_node	*curr;
	char	*temp;
	char	**eepie;
	char	*temp_value;

	i = 0;
	curr = *env;
	len = stack_len(curr);
	// len++;
	eepie = ft_calloc(len, sizeof(char *));
	if (!eepie)
		return (NULL);
	while (i < len - 1)
	{
		if (curr->key)
		{
			temp = ft_strjoin(curr->key, "=");
			if (temp)
			{
				if (curr->value)
				{
					temp_value = ft_strjoin(temp, curr->value);
					free(temp);
					if (temp_value)
					{
						eepie[i] = ft_strdup(temp_value);
						free(temp_value);
					}
				}
				else
					eepie[i] = ft_strdup(temp);
			}
		}
		curr = curr->next;
		i++;
	}
	return (eepie);
}

static int	count_tokens(char *str)
{
	int		count;
	int		i;
	int		quotes;
	char	current;

	i = 0;
	count = 0;
	quotes = 0;
	while (str[i] !=  '\0')
	{
		while (str[i] != '\0' && empties(str[i]))
			i++;
		if (str[i])
			count++;
		while(str[i] && (!empties(str[i]) || quotes))
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				if (quotes && str[i] == current)
					// count++;
					quotes = 0;
				else if (!quotes)
				{
					quotes= 1;
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
	int	i;
	int token_index;
	int start;
	char cur_quo;
	int	tok_len;

	i = 0;
	token_index = 0;
	cur_quo = 0;
	while(str[i])
	{
		while (str[i] && empties(str[i]))
			i++;
		if(str[i])
		{
			start = i;
			i = quote_chk(str, &cur_quo, i);	
			tok_len = i - start;
			tokens[token_index] = malloc(tok_len + 1);
			if (!tokens[token_index])
			{
				free_char_array(tokens);
				return (false);
			}
			ft_strlcpy(tokens[token_index], &str[start], tok_len + 1);
			tokens[token_index] = dollar_check(tokens[token_index], bana->env, bana);
			if(!tokens[token_index])
			{
				free_char_array(tokens);
				return (false);
			}
			token_index++;
		}
	}
	return (true);
}

bool	parsing(char *str, t_bananas *bana)
{
	char	**tokens;
	int		token_count;

	token_count = count_tokens(str);
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
	banananice(bana, tokens, token_count);
	command_search(bana, bana->envp, &bana->env);
	return (true);
}
