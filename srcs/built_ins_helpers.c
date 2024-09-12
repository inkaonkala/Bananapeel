/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:20:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 11:21:47 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_echo(t_bananas *bana)
{
	int i;
	bool n_flag;
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
	if (!(buf = getcwd(NULL, 0)))
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

void handle_exit(t_bananas *bana)
{
	int temp;

	if (bana->tok_num == 1)
	{
		ft_printf("Bye Bye BaNaNaNas!\nexit\n");
		token_cleaner(bana, 0);
		exit(0);
	}
	else if (bana->tok_num >= 2)
	{
		if (number_checker(bana->token[1]))
		{
			temp = ft_atoi(bana->token[1]);
			ft_printf("🍌Bye Bye BaNaNaNas🍌!\nexit(%d)\n", temp);
			while (bana->tok_num > 0)
				token_cleaner(bana, 0);
			exit(temp);	
		}
		else
		{
			(void)temp;
			ft_printf("🍌Bye Bye BaNaNaNas🍌!\nexit\n%s: %s: count your 🍌s!\n", bana->token[0], bana->token[1]);  
			while (bana->tok_num > 0)
				token_cleaner(bana, 2);
			exit(0);
		}
	}
}

void handle_unset(t_bananas *bana, t_node **env)
{
	t_node *node;

	node = NULL;
	token_cleaner(bana, 0);
	while (bana->tok_num >=  1)
	{
		node = *env;
		while (node->next)
		{
			if (!ft_strcmp(node->key, bana->token[0]))
			{
				printf("key = %s\n", node->key);
				token_cleaner(bana, 0);
				free(node->key);
				free(node->value);
				node->key = NULL;
				node->value = NULL;
				remove_node(node);
				break ;
			}
			node = node->next;
		}
	}
	if (bana->is_rdr)
		exit (0);
}

void	remove_node(t_node *node)
{
	t_node *temp;
	if (!node->prev && !node->next)
	{
		(void)temp;
		free(node);
		return ;
	}
	else if (!node->prev && node->next)
	{
		temp = node->next;
		node->next = NULL;
		temp->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else if (node->prev && !node->next)
	{
		temp = node->prev;
		temp->next = NULL;
		node->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else
	{
		temp = node->prev;
		temp->next = node->next;
		temp->next->prev = temp;
		node->prev = NULL;
		node->next = NULL;
		free(node);	
	}
}
