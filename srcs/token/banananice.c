/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banananice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:16:45 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 14:27:24 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_dog(t_bananas *bana, int i)
{	
	if ((ft_strncmp(bana->token[i], "<<<", 3) == 0)
		|| (ft_strncmp(bana->token[i], "<<>", 3) == 0)
		|| (ft_strncmp(bana->token[i], "<<|", 3) == 0))
	{
		printf("Banana !: syntax error after token <<\n");
		clean_struct(bana);
		return (false);
	}
	bana->is_dog = true;
	find_dog(bana, i);
	if (bana->tok_num < 1)
		return (false);
	return (true);
}

static bool	type_check(t_bananas *bana)
{
	int	i;

	i = 0;
	if (ft_strncmp(bana->token[0], "|", 1) == 0)
	{
		printf("Bananas errors\n");
		return (false);
	}
	while (bana->token[i])
	{
		if (ft_strncmp(bana->token[i], "<<", 2) == 0)
		{
			if (!(check_dog(bana, i)))
				return (false);
		}
		if (ft_strncmp(bana->token[i], "|", 1) == 0)
			bana->is_pipe = true;
		if (ft_strncmp(bana->token[i], ">>", 2) == 0
			|| ft_strncmp(bana->token[i], ">", 1) == 0
			|| ft_strncmp(bana->token[i], "<", 1) == 0)
			bana->is_rdr = true;
		i++;
	}
	return (true);
}

bool	banananice(t_bananas *bana, char **tokens, int token_index)
{
	tokens[token_index] = NULL;
	bana->token = tokens;
	bana->tok_num = token_index;
	bana->is_pipe = false;
	bana->is_rdr = false;
	bana->is_dog = false;
	bana->rdr_in_pipe = false;
	bana->outfile_count = 0;
	bana->infile_count = 0;
	bana->original_stdin = -1;
	bana->heredog_interrupted = 0;
	if (!file_malloc(bana))
		return (false);
	del_quotes(bana);
	if (!type_check(bana))
		return (false);
	return (true);
}
