#include "../minishell.h"


int main(int arv, char **arc, char **envp)
{
	(void)arc;
	(void)arv;
	(void)envp;
	//int 	status;

	t_bananas	bana;
	char		*input;

	input = NULL;

	ft_memset(&bana, 0, sizeof(t_bananas));

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			input = readline("🍌banana_peel:");
			if (input == NULL)
			{
				ft_printf("Error in input\n");
				break ;
			}
			//ft_printf("Your input: %s\n", input); //  CHECKER!
			if (*input)
				add_history(input);
			
			// HANDLE SIGNALS BEFORE PARSING!

			if(!parsing(input, &bana, envp))
			{
				ft_printf("Parsing is bananas");
				free(input);
				break ;
			}
			//parsing(input, &bana, envp); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			free(input);
				
		}
	}
	else
	{
		ft_printf("Not active");
	}
	return (0);
}
