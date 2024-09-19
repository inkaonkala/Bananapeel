/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:08 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 14:09:46 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	brake_token_again(t_bananas *bana)
{
	char	**new_tok;
	char	*tok_zero;
	int		i;

	i = 0;
	bana->tok_num = count_tokens(bana->token[0]);
	tok_zero = bana->token[0];
	new_tok = ft_split(tok_zero, ' ');
	free(bana->token[0]);
	while (new_tok[i])
	{
		bana->token[i] = new_tok[i];
		i++;
	}
	bana->token[i] = NULL;
	free(new_tok);
}

void	no_path(t_bananas *bana)
{
	while (bana->tok_num > 1)
	{
		if (strncmp(bana->token[0], "|", 1) != 0)
			printf("Bananas! Nonexistence for such things\n");
		token_cleaner(bana, 0);
	}
	if (bana->tok_num == 1)
	{
		brake_token_again(bana);
		built_ins(bana);
	}
	if (bana->tok_num != 0)
	{
		token_cleaner(bana, 0);
		printf("Bananas! Nonexistence for such things\n");
	}
}
