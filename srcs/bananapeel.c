/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 10:14:28 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int arv, char **arc, char **envp)
{
	(void)arc;
	(void)arv;
	//int 	status;

	t_bananas		bana;
	char			*input;
	t_node			**env;
	struct termios	original_termios;
	
	input = NULL;
	env = NULL; //remove me as I am redundant with ft_calloc two lines below

	ft_memset(&bana, 0, sizeof(t_bananas));
	bana.original_stdin = -1;
	bana.heredog_interrupted = 0;
	env = ft_calloc(1, sizeof(t_node));
	load_list(envp, env);
	setup_terminal(&original_termios);
	if (isatty(STDIN_FILENO))
	{
		signaling();
		while (1)
		{
			input = readline("🍌banana_peel:");
			if (input == NULL)
			{
				write(1, "\n🍌 Goodbye Mate! 🍌\n", 26);
				break ;
			}
			if (*input == '\0' || rl_end == 0)
			{
				free(input);
				continue ;
			}
			add_history(input);

			if(!parsing(input, &bana, env))
			{
				ft_printf("Parsing is bananas");
				if (env)
				 	free_env(env);
				break ;
			}
			if (bana.heredog_interrupted)
			{
				bana.heredog_interrupted = 0;
				continue ;
			}
			//parsing(input, &bana, envp); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			if (input)
				free(input);	
		}
		restore_terminal(&original_termios);
	}
	if (env)
		free_env(env);
	else
	{
		ft_printf("Bananas not ripen yet");
	}
	return (0);
}
