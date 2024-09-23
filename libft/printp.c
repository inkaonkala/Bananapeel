/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:46:11 by jbremser          #+#    #+#             */
/*   Updated: 2024/02/13 11:13:59 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printp(unsigned long int s, int *check)
{
	int	count;

	count = 0;
	if (!s)
		return (print_str("0x0", check));
	while (s)
	{
		count += print_str("0x", check);
		count += cast_hex(s, 16, 0, check);
		return (count);
	}
	return (count);
}
