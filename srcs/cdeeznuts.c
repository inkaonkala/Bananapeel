/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdeeznuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:11:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/16 13:38:54 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	old_pwd_update(t_bananas *bana, char *old_pwd_temp)
{
	free(bana->env->value);
	bana->env->value = ft_strdup(old_pwd_temp);
	while (bana->env->prev)
		bana->env = bana->env->prev;
	free(old_pwd_temp);
}

static char	*new_pwd_update(t_bananas *bana, char *old_pwd_temp)
{
	old_pwd_temp = ft_strdup(bana->env->value);
	free(bana->env->value);
	bana->env->value = getcwd(NULL, 0);
	if (!bana->env->value)
	{
		bana->last_exit_status = 1;
		printf("cwd failed in update_pwds");
		exiting(bana, 1);
	}
	return (old_pwd_temp);
}

void	update_pwds(t_bananas *bana)
{
	char	*old_pwd_temp;
	bool	pwd_updated;

	old_pwd_temp = NULL;
	pwd_updated = false;
	while (bana->env)
	{
		if (!bana->env->next)
			break ;
		if (!ft_strcmp(bana->env->key, "OLDPWD") && pwd_updated == true)
		{
			old_pwd_update(bana, old_pwd_temp);
			break ;
		}
		if (!ft_strcmp(bana->env->key, "PWD") && pwd_updated == false)
		{
			old_pwd_temp = new_pwd_update(bana, old_pwd_temp);
			pwd_updated = true;
			while (bana->env->prev)
				bana->env = bana->env->prev;
		}
		bana->env = bana->env->next;
	}
}

void	homeward_bound(t_bananas *bana)
{
	char	*temp;

	temp = NULL;
	while (bana->env)
	{
		if (!bana->env->next)
			break ;
		if (!ft_strcmp(bana->env->key, "HOME"))
		{
			temp = bana->env->value;
			if (chdir(temp))
			{
				printf("cd failed\n");
				update_pwds(bana);
				exiting(bana, 1);
			}
			break ;
		}
		bana->env = bana->env->next;
	}
}

void	handle_deeznuts(t_bananas *bana)
{
	if (bana->tok_num <= 2)
	{
		token_cleaner(bana, 0);
		if (!bana->token || !bana->token[0] || (!ft_strcmp(bana->token[0], "~")))
		{
			homeward_bound(bana);
			update_pwds(bana);
			while (bana->tok_num > 0)
				token_cleaner(bana, 0);
			return ;
		}
		if (chdir(bana->token[0]))
		{
			printf("cd: %s not set\n", bana->token[0]);
			return ;
		}
		update_pwds(bana);
	}
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (bana->is_rdr)
		exit (0);
}
