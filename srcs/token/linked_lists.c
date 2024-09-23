/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/23 15:33:27 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_node(t_node *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
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
	printf("STRCHR RESULT: [%s]\n", split);
	if (!split)
	{
		dprintf(1, "in if:\n");
		while (node->next)
			node = node->next;
		if (node->value)
			free(node->value);
		node->value = NULL;
		node->key = ft_strdup(str);
	}
	else 
	{
			dprintf(1, "in else\n");
		i = split - str;
		split++;
		if (node->value)
		{
			free(node->value);
		}
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
