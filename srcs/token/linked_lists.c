/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/17 15:33:29 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_node(t_node *node)
{
	t_node	*temp;

	if (!node->prev && !node->next)
	{
		(void)temp;
		free(node->key);
		free(node->value);
		free(node);
		return ;
	}
	else if (!node->prev && node->next)
	{
		temp = node->next;
		node->next = NULL;
		temp->prev = NULL;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
		return ;
	}
	else if (node->prev && !node->next)
	{
		temp = node->prev;
		temp->next = NULL;
		node->prev = NULL;
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
		return ;
	}
	else
	{
		temp = node->prev;
		temp->next = node->next;
		temp->next->prev = temp;
		node->prev = NULL;
		node->next = NULL;
		free(node->key);
		free(node->value);
		free(node);
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
	char *split;
	int i;

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
