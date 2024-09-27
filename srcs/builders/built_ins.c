/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/27 11:52:18 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_env(t_bananas *bana)
{	
	t_node	*temp;

	temp = bana->env;
	while (temp->prev)
	{
		temp = temp->prev;
	}
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (bana->is_rdr)
		exit (0);
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
		handle_unset(bana);
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
