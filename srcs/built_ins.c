/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/27 10:17:36 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	handle_echo(t_bananas *bana)
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

static int	handle_pwd(t_bananas *bana)
{
	char	*buf;

	token_cleaner(bana, 0);
	if (!(buf = getcwd(NULL, 0)))
		return (1);
	ft_putendl_fd(buf, bana->fd_output);
	if (bana->is_rdr)
		exit (0);
	return (0);
}
	// free_null((void *)&buf); oops this was unneeded

static void handle_exit(t_bananas *bana)
{ //mostly done, need to deal with large and negative numbers, as well as EXIT CODES 0-255, how are others dealing with exit codes
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

static void	remove_node(t_node *node)
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


static void handle_unset(t_bananas *bana, t_node **env)
{
	t_node *node;

	node = NULL;
	// printf("%d\n", bana->tok_num);
	if (bana->tok_num == 1)
		token_cleaner(bana, 0);
	else if (bana->tok_num ==  2)
	{
		printf("inside\n");
		node = *env;
		//search for bana-token1 in all of the keys of the LL iterating through them. 
		//remove that whole list and link it back up with the ones around. 
		while (node->next)
		{
			printf("inside while\n");
		//	if (!env)
				// break ;
			if (!ft_strcmp(node->key, bana->token[1]))
			{
				printf("key = %s\n", node->key);
				while (bana->tok_num > 0)
					token_cleaner(bana, 0);
				free(node->key);
				free(node->value);
				node->key = NULL;
				node->value = NULL;
				remove_node(node);
				return ;

			}
			// printf("next");
			node = node->next;
		}
	}
	if (bana->is_rdr)
		exit (0);

}



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