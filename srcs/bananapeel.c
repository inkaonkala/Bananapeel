/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bananapeel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:11:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/26 14:51:29 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_to_bana(t_bananas *bana)
{
	if (!ft_memset(bana, 0, sizeof(t_bananas)))
	{
		printf("Banana errors\n");
		exit(1);
	}
	bana->last_exit_status = 0;
	bana->cmd_paths = NULL;
}

static bool	shell_loop(t_bananas *bana, char *input)
{
	input = readline("🍌banana_peel:");
	if (input == NULL)
	{
		write(1, "\n🍌 Goodbye Mate! 🍌\n", 26);
		return (false);
	}
	if (*input == '\0' || rl_end == 0)
	{
		free(input);
		return (true);
	}
	add_history(input);
	if (!parsing(input, bana))
	{
		printf("Parsing is bananas!\n");
		if (!bana->env)
			free_env(&bana->env);
		return (false);
	}
	if (bana->heredog_interrupted)
		return (true);
	free(input);
	return (true);
}

int	main(int arv, char **arc, char **envp)
{
	t_bananas		bana;
	struct termios	original_termios;

	(void)arc;
	(void)arv;
	add_to_bana(&bana);
	load_list(&bana, envp);
	setup_terminal(&original_termios);
	if (isatty(STDIN_FILENO))
	{
		signaling();
		while (shell_loop(&bana, NULL))
		{
			if (bana.heredog_interrupted)
				bana.heredog_interrupted = 0;
		}
		restore_terminal(&original_termios);
	}
	else
		ft_printf("Bananas not ripen yet!\n");
	clean_banana(&bana);
	return (0);
}
