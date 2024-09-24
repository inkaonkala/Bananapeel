/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:50:14 by iniska            #+#    #+#             */
/*   Updated: 2024/09/24 16:33:01 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_stuff(char **args, char *path)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	if (path)
		free(path);
}

void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

	if (env)
	{
		curr = *env;
		temp = NULL;
		while (curr)
		{
			temp = curr->next;
			free(curr->value);
			free(curr->key);
			free(curr);
			curr = temp;
		}
		*env = NULL;
	}
}

void	free_array(char ***paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(*paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (*paths[i] != NULL)
				free((*paths[i]));
			i++;
		}
	}
	free (*paths);
	*paths = NULL;
}

void	free_line(char **paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free(paths[i]);
			i++;
		}
	}
	free(paths);
	paths = NULL;
}

char	*free_char_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return (NULL);
	i = 0;
	while ((array)[i] != NULL)
	{
		free((array)[i]);
		(array)[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}
