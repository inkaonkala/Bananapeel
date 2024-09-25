/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:02:16 by jbremser          #+#    #+#             */
/*   Updated: 2023/11/20 11:49:35 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	anton(int neg)
{
	if (neg == 1)
		return ((int) FT_LONG_MAX);
	return ((int)-FT_LONG_MAX - 1L);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	blah;
	long	pre;

	i = 0;
	neg = 1;
	blah = 0;
	while ((str[i] == ' ' ) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		pre = blah;
		blah = (blah * 10 + (str[i] - '0'));
		if (blah < 0 || pre > blah)
			return (anton(neg));
		i++;
	}
	return (blah * neg);
}
