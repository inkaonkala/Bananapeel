/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:27:15 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 16:33:12 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Joins a key and value with an '=' sign between them.
   Returns the joined string or NULL if allocation fails. */

static char	*join_key_value(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	if (value)
	{
		result = ft_strjoin(temp, value);
		free(temp);
		return (result);
	}
	return (temp);
}

/* Creates a string representation of an environment variable node.
   Returns the string in the format "key=value" or NULL if it fails. */

static char	*eepiep(t_node *node)
{
	char	*temp;
	char	*result;

	result = NULL;
	if (node->key)
	{
		temp = join_key_value(node->key, node->value);
		if (temp)
		{
			result = ft_strdup(temp);
			free(temp);
		}
	}
	return (result);
}

/* Converts a linked list of environment variables to an array of strings.
   Each string is in the format "key=value".Returns NULL if allocation fails.*/
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
