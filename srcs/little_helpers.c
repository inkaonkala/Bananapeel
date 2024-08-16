/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/08/16 11:57:24 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2024/08/09 16:23:19 by jbremser         ###   ########.fr       */
/*   Updated: 2024/08/13 15:13:17 by iniska           ###   ########.fr       */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/08/13 14:20:40 by jbremser         ###   ########.fr       */
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
	//	free(bana->token[0]);
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

int	number_checker(char *argv)
{
	size_t i;

	i = 0;
	while (i <= ft_strlen(argv) - 1)
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;	
	}
	return (0);

}
	// int	num;
	// int	temp;

	// printf("inside number_checker\n");
	// num = ft_atoi(argv);
	// temp = 0;
	// if (num < 0)
	// 	return (1);
	// if (num == 0)
	// 	return (0);
	// while (num > 0)
	// {
	// 	temp = num % 10;
	// 	if (temp < 0 || temp > 9)
	// 		return (1);
	// 	num /= 10;
	// }
	// return (0);
