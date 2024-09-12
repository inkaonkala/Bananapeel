/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/09/12 10:28:46 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (bana->token[i][j] == '\'' || bana->token[i][j] == '"')
			{
				quote = bana->token[i][j];
				ft_memmove(bana->token[i] + j, bana->token[i] + j + 1, len - j);
				len--;
				while (bana->token[i][j] && bana->token[i][j] != quote)
					j++;
				if (bana->token[i][j] == quote)
				{
					ft_memmove(bana->token[i] + j, bana->token[i] + j + 1, len - j);
					len--;
				}
			}
			else
				j++;
		}
		i++;
	}
}
