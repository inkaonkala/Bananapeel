#include "../minishell.h"


int main()
{
	//(void)arc;
	//(void)arv;
	//int 	status;
	//t_bananas	banana; INSTEAD OF STR USE TOKEN HERE!?
	char		*input;

	input = NULL;
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			ft_printf("banana_peel:");
			input = get_next_line(STDIN_FILENO);
			if (!input)
			{
				ft_printf("Error in input\n");
				break ;
			}
			built_ins(input);
			parsing(input); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			free(input);
			//key_stuff()
		}
	}
	else
	{
		ft_printf("Not active");
		// I don't know what this is
		// we don't need to handle this!
	}
	return (0);
}
