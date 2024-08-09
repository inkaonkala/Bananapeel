#include "../minishell.h"

void    command_search(t_bananas *bana, char **envp)
{
    //if(bana->token[0] != executable)
    //    free_tokens(bana);

    //else if(bana->is_dog && !bana->is_pipe)
    //    here_dog(bana);

    if(bana->is_pipe)
        pipex(bana, envp);
    else if(bana->is_rdr)
        redirections(bana);
    else
        built_ins(bana);

}





// void	command_search(t_bananas *bana, char **envp)
// {
// 	char **token;
	
// 	token = bana->token;
// 	while (*token)
// 	{
// 		// HERE_DOG
// 		/*
// 		if(bana->is_dog && !bana->is_pipe);
// 		*/


// 		//PIPES
// 		if (bana->is_pipe)
// 		{
// 			//ft_printf("Eleven pipers piping\n");
// 			/*
// 			//TO COMPILE WITHOUT PIPEX
			
// 			for (char **env = envp; *env != 0; env++)
//  			{
//     			char *thisEnv = *env;
//     			printf("%s\n", thisEnv);    
//   			}

// 			// END
// 			*/
// 			if(pipex(bana, envp) == -1)
// 				ft_printf("piping is not liking\n");
// 		}
		
// 		//REDIRECTIONS
// 		if (bana->is_rdr)
// 		{
// 			ft_printf("Redirecting bananas\n");
// 			redirections(bana);
// 		}
		
// 		built_ins(bana);  //FIND BUILTINS, EXECUTE, SET TOKEN TO NULL
// 		token++;
// 	}
// 	// Here we could add a checker, that sees if there are tokens left.
// 	// Everytime a token is used, it should be deleted. So, if we have some left at the end
// 	// we now they are invalid and we can print an error message?

// }
