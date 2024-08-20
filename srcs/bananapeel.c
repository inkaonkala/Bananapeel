/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/08/20 14:54:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int arv, char **arc, char **envp)
{
	(void)arc;
	(void)arv;
	//int 	status;

	t_bananas	bana;
	char		*input;
	t_node		**env;

	input = NULL;
	env = NULL;

	ft_memset(&bana, 0, sizeof(t_bananas));
	env  = ft_calloc(1, sizeof(t_node));
  	load_list(envp, env);

	if (isatty(STDIN_FILENO))
	{
		signaling();
		while (1)
		{
			
			input = readline("🍌banana_peel:");
			if (input == NULL)
			{
				write(1, "🍌 Goodbye Mate! 🍌\n", 25);
				break ;
			}
			if (*input == '\0')
			{
				free(input);
				continue ;
			}
			//ft_printf("Your input: %s\n", input); //  CHECKER!
			if (*input == '\0')
			{
				free(input);
				continue ;
			}
			if (*input)
				add_history(input);

			if(!parsing(input, &bana, env))
			{
				ft_printf("Parsing is bananas");
				// if (input)
				// 	free(input);
				break ;
			}
			//parsing(input, &bana, envp); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			if (input)
			{	
				// printf("input?\n");
				free(input);
			}	
		}
	}
	else
	{
		ft_printf("Bananas not ripen yet");
	}
	return (0);
}
