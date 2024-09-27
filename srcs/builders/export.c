/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:10:17 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/27 15:43:54 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	lone_export(t_bananas *bana, t_node *env)
{
	while (env)
	{
		if (env->prev == NULL)
			break;	
		env = env->prev;
	}
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (!env->value)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	token_cleaner(bana, 0);
}

static void	add_lone_node(t_bananas	*bana, char *temp, int len)
{
	t_node	*last;

	last = ft_calloc(1, sizeof(t_node));
	if (!last)
		exiting(bana, 2);
	while (bana->env->next)
		bana->env = bana->env->next;
	if (len == 0)
		last->key = ft_strdup(bana->token[0]);
	else if (len > 0)
	{
		last->key = ft_calloc(len + 1, sizeof(char));
		ft_strlcpy(last->key, bana->token[0], len + 1);
	}
	if (temp == NULL)
		last->value = NULL;
	else if (temp)
		last->value = ft_strdup(temp);
	bana->env->next = last;
	last->prev = bana->env;
	while (bana->env->prev)
		bana->env = bana->env->prev;
}

static void	add_to_env(t_bananas *bana, char *temp, int len)
{
	if (temp)
	{
		add_lone_node(bana, temp, len);
	}
	else if (!temp)
	{
		add_lone_node(bana, temp, 0);
	}
	while (bana->env->prev)
		bana->env = bana->env->prev;
}

static void	search_env(t_bananas *bana, t_node *env, char *temp, int len)
{
	while (env)
	{
		if (env->next == NULL)
		{
			bana->found_in_env = false;
			break ;
		}
		if (!ft_strncmp(env->key, bana->token[0], ft_strlen(env->key)))
		{
			bana->found_in_env = true;
			free(env->value);
			if (temp)
			{
				env->value = ft_strdup(temp);
			}
			else
				env->value = NULL;
			break ;
		}
		env = env->next;
	}
	if (bana->found_in_env == false)
		add_to_env(bana, temp, len);
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
