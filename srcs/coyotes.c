/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/09/05 11:34:58 by jbremser         ###   ########.fr       */
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

// void	del_quotes(t_bananas *bana)
// {
// 	int		i;
// 	size_t	len;

// 	i = 0;
// 	while(bana->token[i])
// 	{
// 		//if(buildercheck(bana->token[i]))
// 		//{
// 		//	i++;
// 		//	continue ;
// 		//}
// 		len = ft_strlen(bana->token[i]);
// 		if(((len > 1 && bana->token[i][0] == '"') && (bana->token[i][len - 1] == '"')) || 
// 			((bana->token[i][0] == '\'') && (bana->token[i][len - 1] == '\'')))
// 		{
// 			ft_memmove(bana->token[i], bana->token[i] + 1, len - 1);
// 			bana->token[i][len - 2] = '\0';
// 			continue ;
// 		}
// 		// else if (one quote, and then the second pair)
// 			trim
// 		i++;
// 	}
// }

void	del_quotes(t_bananas *bana)
{
	int		i;
	int		j;
	size_t	len;
	char	quote;

	i = 0;
	while (bana->token[i])
	{
		j = 0;
		len = ft_strlen(bana->token[i]);
		while (bana->token[i][j])
		{  
			if (bana->token[i][j] == '\'' || bana->token[i][j] == '"')  // Check for both single and double quotes
			{
				quote = bana->token[i][j];  // Remove the opening quote
				ft_memmove(bana->token[i] + j, bana->token[i] + j + 1, len - j);
				len--;
				while (bana->token[i][j] && bana->token[i][j] != quote) 	// Find the matching closing quote
					j++;
				if (bana->token[i][j] == quote)// Remove the closing quote
				{
					ft_memmove(bana->token[i] + j, bana->token[i] + j + 1, len - j);
					len--;
				}
			}
			else
			{
				j++;
			}
		}
		i++;
	}
}


// int	trim_quote(char *str, char *cur_quo, int i)
// {
//     int quotes;
// 	// char *temp;
//     quotes = 0;
// 	// curr_quo
//     while (str[i] && (!empties(str[i]) || quotes))
//     	{
// 	    	if(str[i] == '"' || str[i] == '\'')
// 	    	{
// 	    		if (quotes && str[i] == *cur_quo)
//     			{
// 					printf("\n\ninside trim_quote\n\n");
// 					// ft_strtrim(cur_quo, cur_quo);
// 					printf("\n\nafter trim_quote\n\n");
// 					quotes = 0;
// 				}

//     			else if (!quotes)
//     			{
//     				quotes = 1;
// 				    *cur_quo = str[i];
// 			    }
// 		    }
// 	    i++;			
//     }
//     return (0);
// }

// void	del_taco(t_bananas *bana)
// {
// 	int		i;
// 	int		j;
// 	char	*cur_quo;
// 	// size_t	len;
// 	// char	*temp;

// 	i = 1;
// 	// j = 0;
// 		// printf("\n\ninside delta company\n\n");
// 	// if (bana->token[i])
// 	// 	printf("token[i]\n");
// 	while(bana->token[i])
// 	{
// 		cur_quo = 0;
// 		j = 0;
// 		if (trim_quote(bana->token[i], cur_quo, j))
// 			exit(1);
// 		printf("segfault?\n");
// 		i++;
// 	}
// 	// printf("past while\n");
// }
// 		// //if(buildercheck(bana->token[i]))
// 		// //{
// 		// //	i++;
// 		// //	continue ;
// 		// //}
// 		// len = ft_strlen(bana->token[i]);
// 		// if(((len > 1 && bana->token[i][0] == '"') && (bana->token[i][len - 1] == '"')) || 
// 		// 	((bana->token[i][0] == '\'') && (bana->token[i][len - 1] == '\'')))
// 		// {
// 		// 	ft_memmove(bana->token[i], bana->token[i] + 1, len - 1);
// 		// 	bana->token[i][len - 2] = '\0';
// 		// 	continue ;
// 		// }