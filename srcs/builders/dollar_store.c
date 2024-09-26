/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/26 14:47:22 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_exit_status(char *str, t_bananas *bana)
{
	char	*temp_str;

	temp_str = ft_itoa(bana->last_exit_status);
	if (!temp_str)
		return (str);
	if (ft_strlen(temp_str) <= ft_strlen(str))
		ft_strlcpy(str, temp_str, ft_strlen(temp_str) + 1);
	else
		str = temp_str;
	free(temp_str);
	return (str);
}

static char	*get_var_name(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"'
		&& str[i] != '.')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	j = 0;
	while (j < i - 1)
	{
		var_name[j] = str[j + 1];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

static char	*copy_or_allocate(char *str, char *value)
{
	size_t	value_len;
	char	*temp_str;

	value_len = ft_strlen(value);
	if (value_len <= ft_strlen(str))
		ft_strlcpy(str, value, value_len + 1);
	else
	{
		temp_str = ft_strdup(value);
		str = temp_str;
	}
	return (str);
}

static char	*expand_var_value(char *str, t_node *env, t_bananas *bana)
{
	t_node	*temp_node;
	char	*var_name;

	dprintf(2, "in expand_var");
	var_name = get_var_name(str);
	if (!var_name)
		return (str);
	temp_node = find_key(var_name, env);
	if (temp_node && temp_node->value)
		str = copy_or_allocate(str, temp_node->value);
	else if (ft_strcmp(var_name, "?") == 0)
		str = expand_exit_status(str, bana);
	else
		printf("Variable not found or has no value: %s\n", var_name);
	free(var_name);
	return (str);
}

char	*dollar_check(char *str, t_node *env, t_bananas *bana)
{
	int		i;
	int		s_quote;
	int		d_quote;
	char	*dollar_ptr;
	int		dollar_pos;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	dollar_ptr = ft_strchr(str, 36);
	if (!dollar_ptr)
		return (str);
	dollar_pos = dollar_ptr - str;
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"')
			d_quote = !d_quote;
		if (i == dollar_pos && (!s_quote || (s_quote && d_quote)))
			return (expand_var_value(dollar_ptr, env, bana));
		i++;
	}
	// free(dollar_ptr);
	return (str);
}
