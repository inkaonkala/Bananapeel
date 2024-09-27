/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/27 20:01:34 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_exit_status(char *str, t_bananas *bana)
{
	char	*temp_str;

	temp_str = ft_itoa(bana->last_exit_status);
	if (!temp_str)
		return (str);
	free(str);
	return (temp_str);
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

static char	*expand_var_value(char *str, t_node *env, t_bananas *bana)
{
	char	*temp;
	t_node	*temp_node;
	char	*var_name;

	del_quotes_from_tok(str);
	var_name = get_var_name(str);
	if (!var_name)
		return (str);
	temp_node = find_key(var_name, env);
	if (temp_node && temp_node->value)
		temp = ft_strdup(temp_node->value);
	else if (ft_strcmp(var_name, "?") == 0)
		temp = expand_exit_status(str, bana);
	else
	{
		printf("Variable not found or has no value: %s\n", var_name);
		temp = NULL;
	}
	free(var_name);
	if (!temp)
	{
		return (str);
	}
	free(str);
	return (temp);
}

char	*handle_dollar(char *str, t_node *env, t_bananas *bana, int i)
{
	char	*result;

	if (str[i + 1] == '?')
	{
		result = ft_itoa(bana->last_exit_status);
		if (!result)
			return (str);
		free(str);
		return (result);
	}
	result = NULL;
	return (expand_var_value(str, env, bana));
}

char	*dollar_check(char *str, t_node *env, t_bananas *bana)
{
	int		i;
	int		s_quote;
	int		d_quote;
	char	*dollar_ptr;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	dollar_ptr = ft_strchr(str, 36);
	if (!dollar_ptr)
		return (str);
	while (str[i])
	{
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[i] == '"')
			d_quote = !d_quote;
		if (&str[i] == dollar_ptr)
			if (!s_quote || (s_quote && d_quote))
				return (handle_dollar(str, env, bana, i));
		i++;
	}
	return (str);
}
