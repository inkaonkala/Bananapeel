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
			ft_printf("Your inpupt: %s\n", input);
			if (*input)
				add_history(input);
			if(!parsing(input, &bana, envp))
			{
				ft_printf("Parsing is bananas");
				free(input);
				break ;
			}
			//parsing(input, &bana, envp); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			free(input);
			//key_stuff()
			/*
			THIS NEEDS TO BE DELETED
			// I dont know if this is needed
			if(bana.fd_input != -1)
			{
				close(bana.fd_input);
				bana.fd_input = -1;
			}
			if(bana.fd_output != -1)
			{
				close(bana.fd_output);
				bana.fd_output = -1;
			}
			*/
				
		}
	}
	else
	{
		ft_printf("Not active");
	}
	return (0);
}
