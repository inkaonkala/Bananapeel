/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:17:08 by jbremser          #+#    #+#             */
/*   Updated: 2024/02/13 11:35:31 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*curr;

	i = 1;
	curr = lst;
	if (lst == NULL)
		return (0);
	while (curr -> next != NULL)
	{
		i++;
		curr = curr -> next;
	}
	return (i);
}
