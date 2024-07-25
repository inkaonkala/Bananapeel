#include "../minishell.h"

void	command_search(t_bananas *bana)
{
	char **token;
	
	token = bana->token;
	while (*token)
	{
		//built_ins(token); FIND BUILTINS, EXECUTE, SET TOKEN TO NULL
		if (ft_strncmp(*token, "|", 1 ) == 0)
		{
			ft_printf("Eleven pipers piping\n");
			//pipex(bana);
		}
		if (ft_strncmp(*token, ">>", 2) == 0)
			ft_printf("Redirecting bananas\n");
		token++;
	}

}
