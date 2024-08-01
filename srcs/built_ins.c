#include "../minishell.h"

// static void handle_exit(char *str)
// {
// 	size_t  len;

// 	len = ft_strlen(str);
// 	if (len > 0 && str[len -1] == '\n')
// 		str[len - 1] = '\0';
// 	if (ft_strncmp(str, "exit", 4) == 0)
// 	{
// 		ft_printf("Bye bye BaNaNaNaS!\n");
// 		exit (1);
// 	}
// }

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

static void broom_handle(char *str, t_bananas *bana)
{
	size_t  len;

	len = ft_strlen(str);
	if (len > 0 && str[len -1] == '\n')
		str[len - 1] = '\0';
	if (ft_strncmp(str, "exit", 4) == 0)
	{
		ft_printf("Bye bye BaNaNaNaS!\n");
		exit (1);
	}
	if (ft_strncmp(str, "pwd", 3) == 0)
		handle_pwd(bana);

	// if (ft_strncmp(str, "echo", 4) == 0)
		// handle_echo(str);

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
		broom_handle(*token, bana);
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