/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 14:08:57 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_export(t_bananas *bana, t_node *env)
{
	bool	found_in_env;
	char 	*temp;
	int 	len;
	temp = NULL;
	found_in_env = false;
	if (bana->tok_num == 1)
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
		token_cleaner(bana, 0);
	}
	while (bana->tok_num >= 1)
	{
		if (!ft_strncmp(bana->token[0], "export", 6))
			token_cleaner(bana, 0);
		if (ft_strchr(bana->token[0], '='))
		{
			temp = ft_strchr(bana->token[0], '=');  
			temp++;
			len = temp - bana->token[0] - 1;
		}
		else
			len = ft_strlen(bana->token[0]);
		while (env->next)
		{
			if (!env)
				break ;
			else if (!ft_strncmp(env->key, bana->token[0], len))
			{
				found_in_env = true;
				if (temp)
					env->value = ft_strdup(temp);
			}
			env = env->next;	
		}
		if (found_in_env == false)
		{
			add_end(&env, "");
			if (temp)
			{
				ft_strlcpy(env->key, bana->token[0], len + 1);
				env->value = ft_strdup(temp);
			}
			else
			{	env->key = ft_strdup(bana->token[0]);
				env->value = NULL;
			}
		}
		token_cleaner(bana, 0);
		while (env->prev)
			env = env->prev;
		temp = NULL;
		found_in_env = false;
	}
	if (bana->is_rdr)
		exit (0);
}

static void handle_env(t_bananas *bana, t_node *env)
{
	(void)bana;
	while (env->next)
	{
		if (!env)
			break ;
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (bana->is_rdr)
		exit (0);
}

void print_tokens(t_bananas *bana)
{
	int i;

	i = 0;
	dprintf(2, "tok_num:%d\n", bana->tok_num);
	while(i < bana->tok_num)
	{
		dprintf(2, "Token#%d: %s\n", i + 1, bana->token[i]);
		i++;
	}
}

void built_ins(t_bananas *bana, t_node **env)
{
	size_t	len;
	char 	*bi;

	if (bana->token[0])
	{
		bi = bana->token[0];
		len = ft_strlen(bi);
		if (len > 0 && bi[len - 1]  == '\n')
			bi[len - 1] = '\0';
		else if (ft_strcmp(bi, "exit") == 0)
			handle_exit(bana);
		else if (ft_strcmp(bi, "pwd") == 0)
			handle_pwd(bana);
		else if (ft_strcmp(bi, "echo") == 0)
			handle_echo(bana);
		else if (ft_strcmp(bi, "unset") == 0)
			handle_unset(bana, env);
		else if (ft_strcmp(bi, "env") == 0)
			handle_env(bana, *env);
		else if (ft_strcmp(bi, "export") == 0)
			handle_export(bana, *env);
		else if (ft_strcmp(bi, "cd") == 0)
			handle_deeznuts(bana, *env);
		else
			return ;
	}
}
