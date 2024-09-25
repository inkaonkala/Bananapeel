/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:58:32 by jbremser          #+#    #+#             */
/*   Updated: 2024/04/11 15:38:41 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		len;
	char	ch;

	len = 0;
	ch = (char)c;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
	{
		if (s[len] == ch)
			return ((char *)&s[len]);
		else
			len++;
	}
	if (ch == 0)
		return ((char *)&s[len]);
	return (0);
}
