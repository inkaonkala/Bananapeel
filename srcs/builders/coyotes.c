/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/09/24 11:32:35 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_quotes_from_tok(char *token)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			quote = token[i];
			i++;
			while (token[i] && token[i] != quote)
				token[j++] = token[i++];
			if (token[i] == quote)
				i++;
		}
		else
			token[j++] = token[i++];
	}
	token[j] = '\0';
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

/*
THE OLD VERSION

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
*/
