/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:41:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/19 16:49:52 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	valid(t_bananas *bana, int j)
{
	if ((j < bana->tok_num)
		&& (ft_strncmp(bana->token[j], "|", 1) != 0)
		&& (ft_strncmp(bana->token[j], "<", 1) != 0)
		&& (ft_strncmp(bana->token[j], ">", 1) != 0))
	{
		if (bana->is_rdr)
		{
			if (ft_strncmp(bana->token[j], "echo\0", 5) != 0)
				return (true);
			else
				return (false);
		}
		return (true);
	}
	else
		return (false);
}

static void	merge_it(t_bananas *bana, int i, int j)
{
	int		len;
	char	*new_str;

	if ((ft_strncmp(bana->token[i], "<", 1)) == 0
		|| (ft_strncmp(bana->token[i], ">", 1) == 0))
		return ;
	len = ft_strlen(bana->token[i]) + ft_strlen(bana->token[j]) + 2;
	new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
	{
		ft_printf("Bananas! : Calloc fail in merge\n");
		exiting(bana, 1);
	}
	ft_strlcpy(new_str, bana->token[i], len);
	ft_strlcat(new_str, " ", len);
	ft_strlcat(new_str, bana->token[j], len);
	free(bana->token[i]);
	bana->token[i] = new_str;
	if (j < bana->tok_num && ((ft_strcmp(bana->token[i], "|") != 0)
			|| ft_strncmp(bana->token[i], "<", 1) != 0
			|| ft_strncmp(bana->token[i], ">", 1) != 0
			|| ft_strncmp(bana->token[i], "echo\0", 5) != 0))
		token_cleaner(bana, j);
}

void	token_merge(t_bananas *bana)
{
	int	i;
	int	j;

	i = 0;
	while (i < bana->tok_num)
	{
		if (valid(bana, i))
		{
			j = i + 1;
			while (valid(bana, j))
				merge_it(bana, i, j);
		}
		i++;
	}
}

static bool	dora_is_exploring(t_bananas *bana)
{
	int	no_path;

	no_path = 0;
	while (bana->env->next)
	{
		if (bana->env->next == NULL)
			break ;
		if (ft_strcmp(bana->env->key, "PATH") == 0)
		{
			no_path = 1;
			break ;
		}
		bana->env = bana->env->next;
	}
	while (bana->env->prev)
	{
		if (bana->env->next == NULL)
			break ;
		bana->env = bana->env->prev;
	}
	return (no_path);
}

void	command_search(t_bananas *bana, char **envp, t_node **env)
{
	if (!bana->is_rdr && !bana->is_pipe)
		built_ins(bana);
	if (bana->tok_num > 0)
	{
		token_merge(bana);
		if (bana->is_dog)
			big_stopping(SET, 0);
		if (bana->is_rdr && !bana->is_pipe)
			redirections(bana, envp);
		if (!dora_is_exploring(bana))
			no_path(bana);
		if (bana->tok_num > 0)
		{
			if (bana->is_rdr)
			{
				if (rdr_in_pipes(bana, envp))
					pipex(bana, envp, env);
			}
			else
				pipex(bana, envp, env);
		}
	}
	clean_struct(bana);
}
