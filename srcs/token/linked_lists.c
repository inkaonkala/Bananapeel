/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/24 15:55:19 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_node(t_bananas *bana, const char *key)
{
	t_node	*current;
	t_node	*temp;

	current = bana->env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				bana->env = current->next;
			if (current->next)
				current->next->prev = current->prev;
			temp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}

t_node	*find_last(t_node	*stack)
{
	t_node	*temp;

	if (!stack)
		return (NULL);
	temp = stack;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_node	*parse_str(t_node *node, char *str)
{
	char	*split;
	int		i;

	i = 0;
	split = ft_strchr(str, '=');
	if (!split)
	{
		node->value = NULL;
		node->key = ft_strdup(str);
	}
	else
	{
		i = split - str;
		split++;
		node->value = ft_strdup(split);
		str[i] = '\0';
		node->key = ft_strdup(str);
	}
	return (node);
}

void	load_list(t_bananas *bana, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (add_end(&bana->env, envp[i]))
		{
			free_env(&bana->env);
			write(1, "Error\n", 6);
			exit(1);
		}
		i++;
	}
	return ;
}

int	stack_len(t_node *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}
