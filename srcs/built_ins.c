/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:52:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/15 19:16:43 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



// my brain hurts, tomorrow work!
//check.: figure out a token cleaner to clean out our current token, and remove it from the char** list
// so the next in the line will move into its slot, so the next token will be acted upon by 
// the next function in broom handle which will be the built-in
// THEN I would call this token cleaner again in say echo, as it should clean/free out the next
// tokens

// above is done as of 9.8.24
// work for next work day: ENV, EXPORT, UNSET, and then CD finally. 


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
}

static int	handle_pwd(t_bananas *bana)
{
	char	*buf;

	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	if (!(buf = getcwd(NULL, 0)))
		return (1);
	ft_putendl_fd(buf, bana->fd_output);
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
				token_cleaner(bana, 1);
			exit(0);
		}
	}
}

// static void handle_unset(t_bananas *bana, char **envp)
// {
// 	(void)bana;
// 	(void)envp;
// }

// static char **envp_strjoin(t_bananas *bana, char **envp)
// {
// 	int		i;
// 	int		j;
// 	size_t	len;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// //	i++;
// 	len = (ft_strlen(bana->token[1]));
// 	envp[i] = malloc(len + 1);
// 	if (envp[i] == NULL)
// 		return (NULL);
// 	j = 0;
// 	while (bana->token[1][j])
// 	{
// 		envp[i][j] = bana->token[1][j];
// 		j++;
// 	}
// 	envp[i + 1] = malloc(sizeof(char));
// 	envp[i + 1][1] = '\0';
// 	return (envp);
// }

// static int find_export(t_bananas *bana, char **envp)
// {
// //search for the same key in the envp, and then we will replace that line with the key and anything after
// 	//return the integer for the line number in the envp where this key appears
// 		//or this will iterate through to the end of the envp in which case it returns the last line to the envp, 
// 			//where it will write the new export variable to the bottom of env
// 	int i;

// 	i = 0;
// 	while (envp[i])
// 	{

// 		i++;
// 	}

// }

// static void parse_export(char *token)
// {
// 	//if there is a "=" sign after the key in the export var,
// 	if (ft_strchr(token, "="))
// 		return (1);
// 	return (0);
// }

// static void handle_export(t_bananas *bana, char **envp)
// {
// 	int i;

// 	if (bana->tok_num == 1)
// 	{
// 		i = 0;
// 		while (envp[i])
// 		{
// 			if (!envp[i])
// 				break ;
// 			printf("declare -x %s\n", envp[i]);	
// 			i++;
// 		}
// 	}
// 	else if (bana->tok_num > 1)
// 	{
// 		i = 1;
// 		if (!parse_export(bana->token[i]))
// 			//write to bottom of env, move on to next token, check it for =
	
			
// 			// i = find_export

			
// 	}
// 	// envp = envp_strjoin(bana, envp);
// 	//malloc 2 for \n and \0 then write to envp[i]
// 	//strjoin, token to envp[i]
// 	//
// //	ft_strjoin(envp[i], bana->token[1], ft_strlen(bana->token[1]));
// //	envp[i + 1][0] = '\0';
// }

static void handle_env(t_bananas *bana, t_node *env)
{
	(void)bana;
	while (env->next)
	{
		if (!env)
			break ;
		printf("%s=%s\n", env->key, env->value);	
		env = env->next;
	}
//	ft_putendl_fd("\n", 1);
}

void built_ins(t_bananas *bana, t_node **env)
{
	size_t	len;
	char 	*bi;

	printf("In BI's\n");
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
		// else if (ft_strcmp(bi, "unset") == 0)
		// 	handle_unset(bana, envp);
		else if (ft_strcmp(bi, "env") == 0)
			handle_env(bana, *env);
		// else if (ft_strcmp(bi, "export") == 0)
		// 	handle_export(bana, envp);
		else
			printf("Command '%s' not found\n", bi); 
	}
}




	// temp = ft_atoi(bana->token[1]);

	// printf("this token: %s\n", temp);
	// // printf("after token: %s\n", bana->token[0]);

	// if (!(temp))
	// {
	// 	printf("next token: %s", bana->token[0]);
	// 	ft_printf("Bye Bye BaNaNaNas!\nExit(1)\n");
	// 	bana = token_cleaner(bana, 0);
	// 	exit(1); //add in later, actual exiting functionality
	// }
	// else
	// {
	// 	ft_printf("Bye Bye BaNaNaNas!\nExit(%d)\n", ft_atoi(bana->token[0]));
	// 	bana = token_cleaner(bana, 0);
	// 	exit(ft_atoi(bana->token[0]));  //add in later, actual exiting functionality
	// }

// static void broom_handle(char *token, int tok_num, t_bananas *bana)
// {
// 	size_t  len;

// 	len = ft_strlen(token);
// 	if (len > 0 && token[len -1] == '\n')
// 		token[len - 1] = '\0';
// 	if (ft_strncmp(token, "exit", 4) == 0)
// 	{
// 		ft_printf("Bye bye BaNaNaNaS!\n");
// 		exit (1);
// 	}
// 	if (ft_strncmp(token, "pwd", 3) == 0)
// 	{
// 		// token_cleaner(bana, token);
// 		handle_pwd(bana);
// 	}
// 	if (ft_strncmp(token, "echo", 4) == 0)
// 	{
// 		// token_cleaner(bana, token);
// 		handle_echo(tok_num, bana);
// 	}
// }


// void built_ins(t_bananas *bana)
// {
// 	char **token;

// 	token = bana->token;
// 	while (bana->token)
// 	{
// 		// how will i handles these tokens, say if echo is called, then it needs to save that it is an echo, move on to the next token, and then execute echo to that next token. 
// 		// but then what if the next token is another built-in command
// 		//so my first idea is to have a flag that can be set if a command like echo that requires parameters, so thus the next token, is called. 
// 			//That flag would be set, and we would move to the next token, and run it as an arg of the former token... this could get messy quick tho
// 				// also how would I jump in between different tokens within this while loop.

//     	// handle_exit(*token);
// 		broom_handle(*token, bana->tok_num, bana);
// 		/*
// 		// HANDEL THESE AND SET THE TOKEN TO NULL
// 		hande_echo(*token);
// 		hanlde_pwd(*token);
// 		handle_cd(*token);
// 		handle_env(*token);
// 		handle_export(*token);
// 		handle_unset(*token);
// 		*/
// 		//free_null((void *)token);
// 		bana->token++; 
// 	}
// }
// static int handle_echo(int tok_num, t_bananas *bana)
// {
// 	// char *buf;
// 	int	i = 0;
// 	// buf = ft_strdup(bana->token[tok_num]);
// 	while(i < tok_num - 1)
// 	{
// 		// printf("here\n");
// 		ft_putendl_fd(bana->token[i], bana->fd_output);
// 		i++;
// 		// free(bana->token[tok_num]);
// 	}
// 	return (0);
// }
