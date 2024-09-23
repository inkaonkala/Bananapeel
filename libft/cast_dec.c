/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_dec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:32:43 by jbremser          #+#    #+#             */
/*   Updated: 2024/02/13 11:14:50 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cast_dec(int n, int *check)
{
	int		count;
	char	*low;

	count = 0;
	low = "0123456789";
	if (n == INT_MIN)
		return (count += print_str("-2147483648", check));
	if (n < 0)
	{
		count += print_ch('-', check);
		count += cast_dec(-(n), check);
	}
	else if (n > 9)
	{
		count += cast_dec(n / 10, check);
		count += cast_dec(n % 10, check);
	}
	else
		count += print_ch(low[n], check);
	return (count);
}
