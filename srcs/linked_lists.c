/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 13:22:08 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_node   *parse_str(t_node *node, char *str)
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


int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = malloc(sizeof(t_node));
	if (!last)
		return (1);
	last->next = NULL;
    last = parse_str(last, str);
	if (!(*stack))
	{
		*stack = last;
		last->prev = NULL;
	}
	else
	{
        pre = find_last(*stack); 
		pre->next = last;
		last->prev = pre;
	}
	return (0);
}

void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

   
	curr = *env;
	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	*env = NULL;
}

void load_list(char **envp, t_node **env)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (add_end(env, envp[i]))
        {
            free_env(env);
            write(1, "Error\n", 6);
            exit(1);
        }
        i++;
    }
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
