/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banananice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:16:45 by iniska            #+#    #+#             */
/*   Updated: 2024/09/16 13:46:43 by iniska           ###   ########.fr       */
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
				printf("Banana !: syntax error after token <<\n");
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


void	banananice(t_bananas *bana, char **tokens, int token_index)
{
	tokens[token_index] = NULL;
	bana->token = tokens;
	bana->tok_num = token_index;
	bana->is_pipe = false;
	bana->is_rdr = false;
	bana->is_dog = false;
	bana->outfile_count = 0;
	bana->infile_count = 0;
	bana->original_stdin = -1;
	bana->heredog_interrupted = 0;
	file_malloc(bana);
    del_quotes(bana);
	type_check(bana);
}