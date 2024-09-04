/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:43:50 by iniska            #+#    #+#             */
/*   Updated: 2024/09/04 11:34:59 by etaattol         ###   ########.fr       */
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

	ft_memset(&bana, 0, sizeof(t_bananas));
	bana.skip_command = 0;
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
				free(input);
				break ;
			}
			if (bana.skip_command)
			{
				bana.skip_command = 0;
				free(input);
				continue ;
			}
			//parsing(input, &bana, envp); // this creates the tokens " cat | "boy""" == cat, | , "boy")
			//if (input)
			//{	
			//	// printf("input?\n");
			//	free(input);
			//}
			free(input);
		}
		restore_terminal(&original_termios);
	}
	else
	{
		ft_printf("Bananas not ripen yet");
	}
	return (0);
}
