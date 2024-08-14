/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/08/13 15:13:17 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//OLD
/*
void	token_cleaner(t_bananas *bana, int i)
{
	{
			//handle_specials(bana, i);
		free(bana->token[i]);
		while(i < bana->tok_num - 1)
		{
			bana->token[i] = bana->token[i + 1];
			i++;
		}
		//bana->token[i] = NULL;
		bana->tok_num--;
	}
}
*/


void token_cleaner(t_bananas *bana, int i)
{
	free(bana->token[i]);
	while (i < bana->tok_num - 1)
	{
		// printf("incleaner\n");
		bana->token[i] = bana->token[i + 1];
		i++;	
	}
	bana->tok_num--;
	if (bana->tok_num == 0)
	{
		// free(bana->token[0]);
		bana->token[0] = NULL;
	}
}


int	empties(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int    quote_chk(char *str, char *cur_quo, int i)
{
    int quotes;

    quotes = 0;
    while (str[i] && (!empties(str[i]) || quotes))
    	{
	    	if(str[i] == '"' || str[i] == '\'')
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
	if (ft_strcmp(token, "|") == 0 || ft_strcmp(token, ">") == 0 || strcmp(token, ">>") == 0)
		return (true);
	return (false);
}
