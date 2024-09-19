/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 14:27:11 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_quotes_from_tok(char *token)
{
	int		i;
	size_t	len;
	char	quote;

	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			quote = token[i];
			ft_memmove(token + i, token + i + 1, len-- - i);
			while (token[i] && token[i] != quote)
				i++;
			if (token[i] == quote)
				ft_memmove(token + i, token + i + 1, len -- - i);
		}
		else
			i++;
	}
}

void	del_quotes(t_bananas *bana)
{
	int	i;

	i = 0;
	while (bana->token[i])
	{
		del_quotes_from_tok(bana->token[i]);
		i++;
	}
}
