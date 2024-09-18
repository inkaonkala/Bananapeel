/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:07:40 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 15:32:52 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_delimiter(t_bananas *bana)
{
	int		i;
	int		len;
	char	*deli;

	i = 0;
	while (bana->token[i])
	{
		if (!ft_strcmp(bana->token[i++], "<<"))
		{
			if (!bana->token[i])
				return (ft_strdup(""));
			len = ft_strlen(bana->token[i]);
			deli = malloc(sizeof(char) * (len + 1));
			if (!deli)
			{
				clean_struct(bana);
				return (NULL);
			}
			ft_strlcpy(deli, bana->token[i], len + 1);
			token_cleaner(bana, i);
			return (deli);
		}
	}
	return (NULL);
}
