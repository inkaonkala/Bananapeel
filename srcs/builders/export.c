/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:10:17 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/24 09:20:31 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	lone_export(t_bananas *bana, t_node *env)
{
	while (env->next)
	{
		if (!env)
			break ;
		else if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (!env->value)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	while (env->prev)
	{
		if (!env)
			break ;
		env = env->prev;
	}
	token_cleaner(bana, 0);
}

static void	add_to_env(t_bananas *bana, t_node *env, char *temp, int len)
{
	add_end(&env, bana->token[0]);
	if (temp)
	{
		if (env->value)
			free(env->value);
		ft_strlcpy(env->key, bana->token[0], len + 1);
		env->value = ft_strdup(temp);
	}
	else
	{
		env->key = ft_strdup(bana->token[0]);
		env->value = NULL;
	}
}

static void	search_env(t_bananas *bana, t_node *env, char *temp, int len)
{
	bool	found_in_env;

	found_in_env = false;
	while (env->next)
	{
		if (!env)
		{
			break ;
		}
		else if (!ft_strncmp(env->key, bana->token[0], ft_strlen(env->key)))
		{
			found_in_env = true;
			if (temp)
			{
				free(env->value);
				env->value = ft_strdup(temp);
				break ;
			}
		}
		env = env->next;
	}
	if (found_in_env == false)
		add_to_env(bana, env, temp, len);
	while (env->prev)
		env = env->prev;
}

void	handle_export(t_bananas *bana)
{
	char	*temp;
	int		len;

	temp = NULL;
	if (bana->tok_num == 1)
		lone_export(bana, bana->env);
	while (bana->tok_num >= 1)
	{
		if (!ft_strcmp(bana->token[0], "export"))
			token_cleaner(bana, 0);
		if (ft_strchr(bana->token[0], '='))
		{
			temp = ft_strchr(bana->token[0], '=');
			temp++;
			len = temp - bana->token[0] - 1;
		}
		else
			len = ft_strlen(bana->token[0]);
		search_env(bana, bana->env, temp, len);
		token_cleaner(bana, 0);
		temp = NULL;
	}
	if (bana->is_rdr)
		exit (0);
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
