/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/05 17:55:59 by etaattol         ###   ########.fr       */
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
			bana->is_dog = true;
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
	bana->is_dog = false;
	//bana->is_dog = false;
	bana->outfile_count = 0;
	bana->infile_count = 0;
	file_malloc(bana);
	type_check(bana);
}

char	**list_to_eepie(char **eepie, t_node **env)
{
	int len;
	int i;
	t_node *curr;
	char	*ptr_parking;

	// printf("\n\nlist_to_eepie run\n\n");
	i = 0;
	curr = *env;
	len = stack_len(curr);
	eepie = ft_calloc(len, sizeof(char *));
	while (i < len)
	{
		// ptr_parking = eepie[i];
		// free(ptr_parking); //this may be extra
		eepie[i] = ft_strjoin(curr->key, "=");
		ptr_parking = eepie[i];
		eepie[i] = ft_strjoin(eepie[i], curr->value);
		free(ptr_parking);
		ptr_parking = NULL;
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
	{
		free_envp(envp);
		return (false);
	}
	
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
				free_envp(envp);
				return (false);
			}
			ft_strlcpy(tokens[token_index], &str[start], tok_len + 1);
			token_index++;
		}
	}
	banananice(bana, tokens, token_index);
	// del_quotes(bana);
	command_search(bana, envp, env);

	//CHECKER
	if (envp)
		free_envp(envp);
	return (true);
}


// void print_tokens(char *bana->tokens)
// {
// 	for (int k = 0; k < token_i; k++) 
// 	{
//        ft_printf("Token %d: %s\n", k, tokens[k]);
//        free(tokens[k]); // Free each token after use
//     }
// 	free(tokens);

// 	if (tokens != NULL)
// 	{
// 		ft_printf("%s", &tokens);
// 		free_tokens(tokens);
// 	}
// }

