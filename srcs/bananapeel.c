/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2024/09/13 13:11:18 by iniska           ###   ########.fr       */
/*   Updated: 2024/09/13 16:32:52 by jbremser         ###   ########.fr       */
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
	struct termios	original_termios;
	
	input = NULL;
	if(!ft_memset(&bana, 0, sizeof(t_bananas)))
	{
		printf("Banana errors\n");
		exit(1); // what do we want this to do in this case?
	}
	bana.last_exit_status = 0;
	load_list(&bana, envp);
	setup_terminal(&original_termios);
	if (isatty(STDIN_FILENO))
	{
		signaling();
		while (1)
		{
			input = readline("🍌banana_peel:");
			// printf("\nKey of first line of env: %s  Value of: %s \n", bana.env[0].key, bana.env[0].value);
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

			if(!parsing(input, &bana))
			{
				ft_printf("Parsing is bananas");
				if (!bana.env)
				 	free_env(&bana.env);
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
			// if (env)
			// 	free_env(env);
		}
		restore_terminal(&original_termios);
	}
	else
	{
		ft_printf("Bananas not ripen yet");
	}
	clean_banana(&bana);
	return (0);
}
