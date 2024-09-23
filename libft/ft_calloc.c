/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:01:29 by jbremser          #+#    #+#             */
/*   Updated: 2024/04/26 12:14:33 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	tsize;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	tsize = count * size;
	if (tsize < count && tsize < size)
		return (NULL);
	p = (void *)malloc(tsize);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, tsize);
	return (p);
}
