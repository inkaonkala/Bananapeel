/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/06 12:19:18 by iniska           ###   ########.fr       */
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
	env = NULL;

	if(!ft_memset(&bana, 0, sizeof(t_bananas)))
	{
		printf("Banana errors\n");
		exit (1); // what do we want this to do in this case?
	}
	env = ft_calloc(1, sizeof(t_node));
	if (!env)
	{
		printf("Banana errors\n");
		exit(1); // what do we want this to do in this case?
	}
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
			if (input)
				// printf("input?\n");
				free(input);	
			//if (env)
			//	free_env(env);
		}
		restore_terminal(&original_termios);
	}
	else
	{
		ft_printf("Bananas not ripen yet");
	}
	return (0);
}
