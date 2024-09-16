/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/13 13:21:10 by iniska           ###   ########.fr       */
/*   Updated: 2024/09/13 18:24:28 by jbremser         ###   ########.fr       */
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
			if ((ft_strncmp(bana->token[i], "<<<", 3) == 0) 
				|| (ft_strncmp(bana->token[i], "<<>", 3) == 0)
				|| (ft_strncmp(bana->token[i], "<<|", 3) == 0))
			{
				clean_struct(bana);
				printf("banana: syntax error after token <<\n");
				return ;
			}
			bana->is_dog = true;
			find_dog(bana, i);
			if (bana->tok_num < 1)
			{
				clean_struct(bana);
				return ;
			}
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
	bana->is_dog = false;
	bana->outfile_count = 0;
	bana->infile_count = 0;
	bana->original_stdin = -1; // FOR HEREDOG
	bana->heredog_interrupted = 0; // SIGNALS IN HEREDOG
	file_malloc(bana);
    del_quotes(bana);
	type_check(bana);
}

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

bool	parsing(char *str, t_bananas *bana)

{
	char	**tokens;
	int		token_count;
	int		i;
	int		token_index;
	char	cur_quo;
	int		start;

	i = 0;
	token_index = 0;
	cur_quo = 0;
	token_count = count_tokens(str);
	free_char_array(bana->envp);
	// free(bana->envp);
	bana->envp = list_to_eepie(&bana->env);
    // if (!envp)
    // {
    //     free_tokens(tokens); 
	//     return (false);
    // }
	tokens = ft_calloc((token_count + 1), sizeof(char *));
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
			int tok_len = i - start;
			tokens[token_index] = malloc(tok_len + 1);
			if (!tokens[token_index])
			{
				return (false);
			}
			ft_strlcpy(tokens[token_index], &str[start], tok_len + 1);
			tokens[token_index] = dollar_check(tokens[token_index], bana->env, bana);
			token_index++;
		}
	}
	banananice(bana, tokens, token_index);
	command_search(bana, bana->envp, &bana->env);
	// clean_command_line();
	return (true);
}
