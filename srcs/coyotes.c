/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coyotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:02:54 by iniska            #+#    #+#             */
/*   Updated: 2024/08/29 11:43:41 by iniska           ###   ########.fr       */
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

void	del_quotes(t_bananas *bana)
{
	int		i;
	size_t	len;

	i = 0;
	while(bana->token[i])
	{
		//if(buildercheck(bana->token[i]))
		//{
		//	i++;
		//	continue ;
		//}
		len = ft_strlen(bana->token[i]);
		ft_printf("%s\n", bana->token[i]);
		if(((len > 1 && bana->token[i][0] == '"') && (bana->token[i][len - 1] == '"')) || 
			((bana->token[i][0] == '\'') && (bana->token[i][len - 1] == '\'')))
		{
			ft_memmove(bana->token[i], bana->token[i] + 1, len - 1);
			bana->token[i][len - 2] = '\0';
			continue ;
		}
		ft_printf("		%s\n", bana->token[i]);
		i++;
	}
}
