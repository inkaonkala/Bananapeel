/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:11:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/17 11:41:20 by jbremser         ###   ########.fr       */
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
		exit(1);
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
				printf("Parsing is bananas!\n");
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
				free(input);
		}
		restore_terminal(&original_termios);
	}
	else
		printf("Bananas not ripen yet!\n");
	clean_banana(&bana);
	return (0);
}
