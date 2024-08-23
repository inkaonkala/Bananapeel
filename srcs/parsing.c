/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/23 11:34:02 by iniska           ###   ########.fr       */
/*   Updated: 2024/08/22 15:12:42 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	type_check(t_bananas *bana)
{
	int	i;

	i = 0;
	while(bana->token[i])
	{		
		if (ft_strncmp(bana->token[i], "<<", 2) == 0)
		{
			find_dog(bana, i);
			//if (ft_strlen(bana->token[i]) == 2)
			//	i++;
		}
		
		if(ft_strncmp(bana->token[i], "|", 1) == 0)
		{
			bana->is_pipe = true;
		}
		if(ft_strncmp(bana->token[i], ">>", 2) == 0 || 
			ft_strncmp(bana->token[i], ">", 1) == 0 || 
			ft_strncmp(bana->token[i], "<", 1) == 0)
			bana->is_rdr = true;
		i++;		
	}	
}

static void	banananice(t_bananas *bana, char **tokens, int token_index)
{
	tokens[token_index] = NULL;
	bana->token = tokens;
	bana->tok_num = token_index;
	bana->is_pipe = false;
	bana->is_rdr = false;
	//bana->is_dog = false;
	
	type_check(bana);
}

static char	**list_to_eepie(char **eepie, t_node **env)
{
	int len;
	int i;
	t_node *curr;

	i = 0;
	curr = *env;
	len = stack_len(curr) + 1;
	eepie = ft_calloc(len, sizeof(char *));
	while (i < len - 1)
	{
		eepie[i] = ft_strjoin(curr->key, "=");
		eepie[i] = ft_strjoin(eepie[i], curr->value);
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

bool	parsing(char *str, t_bananas *bana, t_node **env)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		token_index;
	char	cur_quo;
	char	**envp;
	int		start;

	i = 0;
	token_index = 0;
	cur_quo = 0;
	envp = NULL;
	token_count = count_tokens(str);
	envp = list_to_eepie(envp, env);
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
			tokens[token_index] = malloc(tok_len + 1);
			if (!tokens[token_index])
			{
				return (false);
			}
			ft_strlcpy(tokens[token_index], &str[start], tok_len + 1);
			token_index++;
		}
	}
	banananice(bana, tokens, token_index);
	command_search(bana, envp, env);

	//CHECKER
	return (true);
}

/*
	//CHECKER!!
	//for (int k = 0; k < token_i; k++) 
	//{
    //    ft_printf("Token %d: %s\n", k, tokens[k]);
    //    free(tokens[k]); // Free each token after use
    //}
	//free(tokens);

	if (tokens != NULL)
	{
		ft_printf("%s", &tokens);
		free_tokens(tokens);
	}
*/

