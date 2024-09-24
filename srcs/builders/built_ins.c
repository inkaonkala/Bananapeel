/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/24 12:24:43 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_env(t_bananas *bana)
{	
	while (bana->env->next)
	{
		if (bana->env->next == NULL)
		{		
			break ;
		}
		if (bana->env->value)
			printf("%s=%s\n", bana->env->key, bana->env->value);
		bana->env = bana->env->next;
	}
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (bana->is_rdr)
		exit (0);
	while (bana->env->prev)
		bana->env = bana->env->prev;
}

void	print_tokens(t_bananas *bana)
{
	int	i;

	i = 0;
	dprintf(2, "tok_num:%d\n", bana->tok_num);
	while (i < bana->tok_num)
	{
		dprintf(2, "Token#%d: %s\n", i + 1, bana->token[i]);
		i++;
	}
}

static void	send_to_bob(t_bananas *bana, char *bi)
{
	if (ft_strcmp(bi, "exit") == 0)
		handle_exit(bana);
	else if (ft_strcmp(bi, "pwd") == 0)
		handle_pwd(bana);
	else if (ft_strcmp(bi, "echo") == 0)
	{
		if (bana->rdr_in_pipe)
			echo_pipe(bana);
		else
			handle_echo(bana);
	}
	else if (ft_strcmp(bi, "unset") == 0)
		handle_unset(bana, &bana->env);
	else if (ft_strcmp(bi, "env") == 0)
		handle_env(bana);
	else if (ft_strcmp(bi, "export") == 0)
		handle_export(bana);
	else if (ft_strcmp(bi, "cd") == 0)
		handle_deeznuts(bana);
	else
		return ;
}

void	built_ins(t_bananas *bana)
{
	size_t	len;
	char	*bi;

	if (bana->token[0])
	{
		bi = bana->token[0];
		len = ft_strlen(bi);
		if (len > 0 && bi[len - 1] == '\n')
			bi[len - 1] = '\0';
		send_to_bob(bana, bi);
		return ;
	}
}
