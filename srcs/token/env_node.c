/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:27:15 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 09:48:37 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*eepiep(t_node *node)
{
	char	*temp;
	char	*temp_value;
	char	*result;

	result = NULL;
	if (node->key)
	{
		temp = ft_strjoin(node->key, "=");
		if (temp)
		{
			if (node->value)
			{
				temp_value = ft_strjoin(temp, node->value);
				free(temp);
				if (temp_value)
				{
					result = ft_strdup(temp_value);
					free(temp_value);
				}
			}
			else
			{
				result = ft_strdup(temp);
				free(temp);
			}
		}
	}
	return (result);
}

char	**list_to_eepie(t_node **env)
{
	int		len;
	int		i;
	t_node	*curr;
	char	**eepie;

	i = 0;
	curr = *env;
	len = stack_len(curr);
	eepie = ft_calloc(len, sizeof(char *));
	if (!eepie)
		return (NULL);
	while (i < len - 1)
	{
		eepie[i] = eepiep(curr);
		if (!eepie[i])
		{
			free_line(eepie, len);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	return (eepie);
}
