/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:20:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/27 19:25:22 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_pipe(t_bananas *bana)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	if (bana->tok_num > 1)
	{
		while (bana->token[i][0] != '|' && bana->token[i][0] != '\0')
		{
			ft_printf("%s ", bana->token[i]);
			i++;
		}
	}
}

void	handle_echo(t_bananas *bana)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	if (bana->tok_num == 1)
		printf("\n");
	else if (bana->tok_num > 1)
	{
		if (ft_strcmp(bana->token[1], "-n") == 0)
		{
			token_cleaner(bana, 1);
			n_flag = true;
		}
		while (i <= bana->tok_num - 2)
			printf("%s ", bana->token[i++]);
		if (bana->tok_num >= 2)
			printf("%s", bana->token[bana->tok_num - 1]);
		if (n_flag == false)
			printf("\n");
	}
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (bana->is_rdr)
		exit (0);
}

int	handle_pwd(t_bananas *bana)
{
	char	*buf;

	token_cleaner(bana, 0);
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		bana->last_exit_status = 1;
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	bana->last_exit_status = 0;
	if (bana->is_rdr)
		exit (0);
	return (0);
}

void	handle_unset(t_bananas *bana)
{
	token_cleaner(bana, 0);
	while (bana->tok_num >= 1)
	{
		remove_node(bana, bana->token[0]);
		token_cleaner(bana, 0);
	}
	if (bana->is_rdr)
		exit(0);
}

t_node	*find_key(char *key, t_node *env)
{
	while (env)
	{
		if (env->prev == NULL)
			break ;
		env = env->prev;
	}
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}
