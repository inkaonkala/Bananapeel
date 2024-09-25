/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:19:28 by iniska            #+#    #+#             */
/*   Updated: 2024/09/25 11:58:07 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_commands(t_bananas *bana)
{
	int	j;

	j = 0;
	while (bana->token[j])
	{
		while (bana->token[j][0] != '|')
		{
			if (bana->token[j][0] == '<' || bana->token[j][0] == '>')
				return ;
			j++;
		}
		if (bana->token[j][0] == '|')
		{	
			while (j > 0)
			{
				token_cleaner(bana, 0);
				j--;
			}
			token_cleaner(bana, 0);
		}
		j++;
	}
}

static void	close_files(t_bananas *bana)
{
	int	i;

	i = 0;
	while (i < bana->infile_count)
	{
		close(bana->in_files[i]);
		i++;
	}
	i = 0;
	while (i < bana-> outfile_count)
	{
		close(bana->out_files[i]);
		i++;
	}
}

static bool	rdr_checker(t_bananas *bana)
{
	int	i;

	i = 0;
	while (bana->token[i])
	{
		if (strncmp(bana->token[i], "<", 1) == 0
			|| strncmp(bana->token[i], ">", 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	rdr_in_pipes(t_bananas *bana, char **envp)
{
	bana->rdr_in_pipe = true;
	clean_commands(bana);
	redirections(bana, envp);
	if (bana->tok_num > 0)
	{
		while (bana->token[0][0] != '|' && bana->tok_num > 1)
			token_cleaner(bana, 0);
		token_cleaner(bana, 0);
		if (bana->tok_num > 0)
		{
			if (rdr_checker(bana))
				rdr_in_pipes(bana, envp);
		}
		bana->is_rdr = false;
		return (true);
	}
	return (false);
}
