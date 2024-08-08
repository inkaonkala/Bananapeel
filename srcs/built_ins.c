#include "../minishell.h"

static int token_cleaner(t_bananas *bana, char *token)
{
	int i;

	i = 0;
	while (i < )

// my brain hurts, tomorrow work!
// figure out a token cleaner to clean out our current token, and remove it from the char** list
// so the next in the line will move into its slot, so the next token will be acted upon by 
// the next function in broom handle which will be the built-in
// THEN I would call this token cleaner again in say echo, as it should clean/free out the next
// tokens
}

static int handle_echo(int tok_num, t_bananas *bana)
{
	// char *buf;
	int	i = 0;
	// buf = ft_strdup(bana->token[tok_num]);
	while(i < tok_num - 1)
	{
		// printf("here\n");
		ft_putendl_fd(bana->token[i], bana->fd_output);
		i++;
		// free(bana->token[tok_num]);
	}
	return (0);
}

static int handle_pwd(t_bananas *bana)
{
	char	*buf;

	// printf("fd:%d\n", bana->fd_output);	
	if (!(buf = getcwd(NULL, 0)))
		return (1);
	ft_putendl_fd(buf, bana->fd_output);
	// free_null((void *)&buf); oops this was unneeded
	return (0);
}

static void broom_handle(char *token, int tok_num, t_bananas *bana)
{
	size_t  len;

	len = ft_strlen(token);
	if (len > 0 && token[len -1] == '\n')
		token[len - 1] = '\0';
	if (ft_strncmp(token, "exit", 4) == 0)
	{
		ft_printf("Bye bye BaNaNaNaS!\n");
		exit (1);
	}
	if (ft_strncmp(token, "pwd", 3) == 0)
	{
		token_cleaner(bana, token);
		handle_pwd(bana);
	}
	if (ft_strncmp(token, "echo", 4) == 0)
	{
		token_cleaner(bana, token);
		handle_echo(tok_num, bana);
	}
}

void built_ins(t_bananas *bana)
{
	char **token;

	token = bana->token;
	while (*token)
	{
		// how will i handles these tokens, say if echo is called, then it needs to save that it is an echo, move on to the next token, and then execute echo to that next token. 
		// but then what if the next token is another built-in command
		//so my first idea is to have a flag that can be set if a command like echo that requires parameters, so thus the next token, is called. 
			//That flag would be set, and we would move to the next token, and run it as an arg of the former token... this could get messy quick tho
				// also how would I jump in between different tokens within this while loop.

    	// handle_exit(*token);
		broom_handle(*token, bana->tok_num, bana);
		/*
		// HANDEL THESE AND SET THE TOKEN TO NULL
		hande_echo(*token);
		hanlde_pwd(*token);
		handle_cd(*token);
		handle_env(*token);
		handle_export(*token);
		handle_unset(*token);
		*/
		//free_null((void *)token);
		token++; 
	}
}