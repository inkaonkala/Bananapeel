/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:29:28 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/05 18:02:37 by jbremser         ###   ########.fr       */
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
    // printf("inside find last\n");
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
        ft_printf("no split\n");
        node->value = NULL;
        node->key = ft_strdup(str);
    }
    else
    {
        if (node->key)
            free(node->key);
        if (node->value)
            free(node->value);
        i = split - str;
        split++;
        // if (*split == '\0')
        node->value = ft_strdup(split);
        str[i] = '\0';
        node->key = ft_strdup(str);
    }
    return (node);
}
    // split++;
        // ft_printf("i: %d\n", i);
        // ft_printf("value: %s\n", node->value);
        // free(split);
        // ft_strlcpy(node->key, str, i);
        // ft_printf("key: %s\n", node->key);


int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = ft_calloc(1, sizeof(t_node));
	if (!last)
		return (1);
    last->key = NULL;
    last->value = NULL;
    last = parse_str(last, str);
	last->next = NULL;
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
       // printf("\n\nthe old last node is %s=%s and the new last node is %s=%s\n\n", pre->key, pre->value, last->key, last->value);
	}
	return (0);
}
    // printf("inside add_end\n");
	// last->line = ft_strdup(str); //////// added to function above to split the lines
    // printf("after strdup; line: %s\n", last->line);
        // printf("inside add_end if\n");
        // printf("inside add_end else\n");

void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

   
	curr = *env;
	temp = NULL;
    printf("inside FREE_ENV\n");
	while (curr)
	{
        free(curr->key);
        free(curr->value);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
    free(env);
    // env = NULL;
}

void load_list(char **envp, t_node **env)
{
    int i;

    i = 0;
    // printf("Load_list\n");
    while (envp[i])
    {
        if (add_end(env, envp[i]))
        {
            free_env(env);
            write(1, "Error\n", 6);
            exit(1);
        }
        // printf("another line\n");
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
		i++;
		stack = stack->next;
	}
	return (i);
}