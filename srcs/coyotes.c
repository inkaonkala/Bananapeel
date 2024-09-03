/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/09/03 15:16:32 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
static bool	buildercheck(char *str)
{
	if(strcmp(str, "echo"))
		return (true);

	if(strcmp(str, "export"))
		return (true);
	else
		return (false);
}
*/

void	del_quotes(t_bananas *bana)
{
	int		i;
	size_t	len;

	i = 0;
	while(bana->token[i])
	{
		//if(buildercheck(bana->token[i]))
		//{
		//	i++;
		//	continue ;
		//}
		len = ft_strlen(bana->token[i]);
		if(((len > 1 && bana->token[i][0] == '"') && (bana->token[i][len - 1] == '"')) || 
			((bana->token[i][0] == '\'') && (bana->token[i][len - 1] == '\'')))
		{
			ft_memmove(bana->token[i], bana->token[i] + 1, len - 1);
			bana->token[i][len - 2] = '\0';
			continue ;
		}
		i++;
	}
}

int	trim_quote(char *str, char *cur_quo, int i)
{
    int quotes;
	// char *temp;
    quotes = 0;
    while (str[i] && (!empties(str[i]) || quotes))
    	{
	    	if(str[i] == '"' || str[i] == '\'')
	    	{
	    		if (quotes && str[i] == *cur_quo)
    			{
					printf("\n\ninside trim_quote\n\n");
					ft_strtrim(cur_quo, cur_quo);
					printf("\n\nafter trim_quote\n\n");
					quotes = 0;
				}

    			else if (!quotes)
    			{
    				quotes = 1;
				    *cur_quo = str[i];
			    }
		    }
	    i++;			
    }
	if (quotes)
	{
		printf("Syntax error (OMG THE LEAKS)\n");
		//clean here
		return(1);
	}	
    return (0);
}

void	del_taco(t_bananas *bana)
{
	int		i;
	int		j;
	char	*cur_quo;
	// size_t	len;
	// char	*temp;

	i = 1;
	// j = 0;
		// printf("\n\ninside delta company\n\n");
	// if (bana->token[i])
	// 	printf("token[i]\n");
	while(bana->token[i])
	{
		cur_quo = 0;
		j = 0;
		if (trim_quote(bana->token[i], cur_quo, j))
			exit(1);
		i++;
	}
	// printf("past while\n");
}
		// //if(buildercheck(bana->token[i]))
		// //{
		// //	i++;
		// //	continue ;
		// //}
		// len = ft_strlen(bana->token[i]);
		// if(((len > 1 && bana->token[i][0] == '"') && (bana->token[i][len - 1] == '"')) || 
		// 	((bana->token[i][0] == '\'') && (bana->token[i][len - 1] == '\'')))
		// {
		// 	ft_memmove(bana->token[i], bana->token[i] + 1, len - 1);
		// 	bana->token[i][len - 2] = '\0';
		// 	continue ;
		// }