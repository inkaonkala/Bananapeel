/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/27 10:34:48 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_export(t_bananas *bana, t_node *env)
{
	if (bana->tok_num == 1)
	{
		while (env->next)
		{
			if (!env)
				break ;
			printf("declare -x %s=%s\n", env->key, env->value);	
			env = env->next;
		}
		token_cleaner(bana, 0);
	}
	else if (bana->tok_num > 1)
		return ;
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

void built_ins(t_bananas *bana, t_node **env)
{
	size_t	len;
	char 	*bi;

	// printf("In BI's\n");
	if (bana->token[0])
	{
		bi = bana->token[0];
		len = ft_strlen(bi);
		// printf("bi:%s\n", bi);
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
		else
			return ;
			//send to pipes
			// printf("Command '%s' not found\n", bi); 
	}
}
