#include "../minishell.h"

void	command_search(t_bananas *bana, char **envp)
{
	char **token;
	
	token = bana->token;
	while (*token)
	{
		built_ins(bana);
		//built_ins(token); FIND BUILTINS, EXECUTE, SET TOKEN TO NULL
		
		//PIPES
		if (ft_strncmp(*token, "|", 1 ) == 0)
		{
			//ft_printf("Eleven pipers piping\n");
			
			//TO COMPILE WITHOUT PIPEX
//			for (char **env = envp; *env != 0; env++)
 // 			{
//    			char *thisEnv = *env;
//    			printf("%s\n", thisEnv);    
//  			}

			// END
			
			if(pipex(bana, envp) == -1)
				ft_printf("piping is not liking\n");
		}
		
		//REDIRECTIONS
		if (ft_strncmp(*token, ">>", 2) == 0 || ft_strncmp(*token, ">", 1) == 0)
		{
			ft_printf("Redirecting bananas\n");
			//redirections(bana);
		}
			

		
		// SIGNALS ?!
		token++;
	}
	// Here we could add a checker, that sees if there are tokens left.
	// Everytime a token is used, it should be deleted. So, if we have some left at the end
	// we now they are invalid and we can print an error message?

}
