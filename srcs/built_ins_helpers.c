/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:20:14 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 11:16:12 by jbremser         ###   ########.fr       */
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
		return (1);
	printf("%s\n", buf);
	if (bana->is_rdr)
		exit (0);
	return (0);
}


size_t exit_coder(char *argv)
{
    size_t i = 0;
    unsigned long result = 0;

    while (argv[i] != '\0')
    {
        if (!isdigit(argv[i]))
            return (0);
        i++;
    }
    i = 0;
    while (argv[i] != '\0')
    {
        if (result > (unsigned long)(INT_MAX / 10) || 
            (result == (unsigned long)(INT_MAX / 10) && (argv[i] - '0') > (INT_MAX % 10)))
            	result = result % ((unsigned long)INT_MAX + 1);
        result = result * 10 + (argv[i] - '0');
        i++;
    }
	return (result % 256);
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
			temp = exit_coder(bana->token[1]);
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
	// printf("%d\n", bana->tok_num);
	// if (bana->tok_num == 1)
		// printf("amount of tokens = %d\n", bana->tok_num);
		// printf("inside\n");
		// while tok_num > 1
		//search for bana-token1 in all of the keys of the LL iterating through them. 
		//remove that whole list and link it back up with the ones around. 
			// printf("inside inner while loop\n");
		//	if (!env)
				// break ;
				// printf("after token cleaner\n");
				// return ;
				// printf("after remove node\n");
			// printf("next");
		// printf("after inner loop\n");


void	remove_node(t_node *node)
{
	t_node *temp;
	if (!node->prev && !node->next) //only node
	{
		(void)temp;
		free(node);
		return ;
	}
	else if (!node->prev && node->next) //first node
	{
		temp = node->next;
		node->next = NULL;
		temp->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else if (node->prev && !node->next) //last node
	{
		temp = node->prev;
		temp->next = NULL;
		node->prev = NULL;
		free(node);
		node = temp;
		return ;
	}
	else
	//needs to handle for first node, last node, two nodes only, edges
	{
		temp = node->prev;
		temp->next = node->next;
		temp->next->prev = temp;
		node->prev = NULL;
		node->next = NULL;
		free(node);	
	}
}