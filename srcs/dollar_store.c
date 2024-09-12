/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 14:29:21 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_node *find_key(char *key, t_node *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		else
			env = env->next;
	}
    return (NULL);
}

static char *expand_var(char *str, t_node *env, t_bananas *bana)
{
	t_node	*temp_node;
	char	*var_name;
	int 	i;
	int 	j;
	size_t		value_len;
	char	*temp_str;
	
	if (str[1] == '?')
	{
		temp_str = ft_itoa(bana->last_exit_status);
		if (!temp_str)
			return (str);
		if (ft_strlen(temp_str) <= ft_strlen(str))
			ft_strlcpy(str, temp_str, ft_strlen(temp_str) + 1);
		else
			str = temp_str;
		free (temp_str);
		return (str);
	}
	
	value_len = 0;
	i = 1;
	while (str[i] && (str[i] != ' ' && str[i] != '\0' && str[i] != '\'' && str[i] != '"' && str[i] != '.'))
        i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (str);	
	j = 1;
	while (j < i)
	{
		var_name[j - 1] = str[j];
		j++;
	}	
	var_name[j - 1] = '\0';
    temp_node = find_key(var_name, env);
	if (temp_node && temp_node->value)
	{
		value_len = ft_strlen(temp_node->value);
		if (value_len <= ft_strlen(str))
			ft_strlcpy(str, temp_node->value, value_len + 1);
		else
			{
				temp_str = ft_strdup(temp_node->value);
				if (temp_str)
				{
					free (str);
					str = temp_str;
				}
			}
	}
	else if (ft_strcmp(var_name, "?") == 0)
	{
		temp_str = ft_itoa(bana->last_exit_status);
		value_len = ft_strlen(temp_str);
		if (value_len <= ft_strlen(str))
			ft_strlcpy(str, temp_str, value_len + 1);
		else
		{
			if (temp_str)
			{
				free (str);
				str = temp_str;
			}
		}
	}
	else
		printf("Variable not found or has no value: %s\n", var_name);
	free(var_name);
	return (str);
} 

char	*dollar_check(char *str, t_node *env, t_bananas *bana)
{
	int i = 0;
	int single_quote = 0;
	int double_quote = 0;
	char *dollar_ptr;

	if (!(dollar_ptr = ft_strchr(str, 36)))
		return (str);

	int dollar_pos = dollar_ptr - str;

	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;

		else if (str[i] == '"')
			double_quote = !double_quote;
		
		if (i == dollar_pos)
		{
			if (!single_quote || (single_quote && double_quote))
			{
				str = expand_var(dollar_ptr, env, bana);
				return (str);
			}
			else
				return (str);
		}
		i++;
	}
	return (str);
}
