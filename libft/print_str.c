/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:04:56 by jbremser          #+#    #+#             */
/*   Updated: 2024/02/13 11:12:38 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str(char *s, int *check)
{
	int	count;

	count = 0;
	if (!s)
		return (print_str("(null)", check));
	while (*s)
		count += print_ch(*s++, check);
	return (count);
}
