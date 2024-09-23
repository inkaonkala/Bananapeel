/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:25:10 by jbremser          #+#    #+#             */
/*   Updated: 2024/02/13 11:12:57 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	j;

	j = 0;
	if (start > ft_strlen(s) || s[0] == '\0' || len == 0)
	{
		dst = malloc(1);
		dst[0] = '\0';
		return (dst);
	}
	if (len > (ft_strlen(s + start)))
		len = (ft_strlen(s + start));
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	while (s[start] && j < len)
		dst[j++] = s[start++];
	dst[j] = '\0';
	return (dst);
}
