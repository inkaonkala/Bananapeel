/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:36:35 by jbremser          #+#    #+#             */
/*   Updated: 2024/06/20 14:51:17 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cast_hex(unsigned long long n, unsigned int b, int x, int *check)
{
	int		count;
	char	*up;
	char	*low;

	count = 0;
	low = "0123456789abcdef";
	up = "0123456789ABCDEF";
	if (n > b - 1)
	{
		count += cast_hex(n / b, b, x, check);
		count += cast_hex(n % b, b, x, check);
	}
	else
	{
		if (x == 0)
			count += print_ch(low[n], check);
		else if (x == 1)
			count += print_ch(up[n], check);
	}
	return (count);
}
