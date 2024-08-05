/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:58 by iniska            #+#    #+#             */
/*   Updated: 2024/07/22 16:07:19 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	free_tokens(char **tokens)
{
	int	k;

	k = 0;
	while (tokens[k])
	{
		free(tokens[k]);
		k++;
	}
	free(tokens);
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

// takes input and splits due to pipes and null to seperate nodes
bool	parsing(char *str, t_bananas *bana, char **envp)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		token_index;
	char	cur_quo;

	int start;

	i = 0;
	token_index = 0;
	cur_quo = 0;

	token_count = count_tokens(str);

	tokens = malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (false);
	
	while(str[i])
	{
		while (str[i] && empties(str[i]))
			i++;
		if(str[i])
		{
			start = i;

			i = quote_chk(str, &cur_quo, i);	
			int tok_len = i - start; //HERE HERE

			// HERE DOG!
			if(tok_len == 2 && ft_strncmp(&str[start], "<<", 2) == 0)
				find_dog(str);
				
			else
			{
				tokens[token_index] = malloc(tok_len + 1);
				if (!tokens[token_index])
				{
					//free(tokens); ?
					return (false);
				}
				ft_strlcpy(tokens[token_index], &str[start], tok_len + 1);
				token_index++;
			}
		}
	}
	tokens[token_index] = NULL;
	bana->token = tokens; // tokens set to struct
	bana->tok_num = token_index;

	command_search(bana, envp);

	//CHECKER!!
	//for (int k = 0; k < token_i; k++) 
	//{
    //    ft_printf("Token %d: %s\n", k, tokens[k]);
    //    free(tokens[k]); // Free each token after use
    //}
	//free(tokens);
	//remember to free all tokens!
	// CHECKER!!
	free_tokens(tokens);

	return (true);
}



