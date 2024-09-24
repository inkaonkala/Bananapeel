/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:08 by iniska            #+#    #+#             */
/*   Updated: 2024/09/24 14:21:37 by jbremser         ###   ########.fr       */
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

int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = malloc(sizeof(t_node));
	if (!last)
		return (1);
	last->next = NULL;
	last = parse_str(last, str);
	if (!(*stack))
	{
		*stack = last;
		last->prev = NULL;
	}
	else
	{
		pre = find_last(*stack);
		pre->next = last;
		last->prev = pre;
	}
	return (0);
}
