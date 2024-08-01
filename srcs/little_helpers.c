/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/07/22 16:07:09 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
