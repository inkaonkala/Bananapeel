/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:37:19 by iniska            #+#    #+#             */
/*   Updated: 2024/09/24 09:57:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (get_heredog_status() == IN_HEREDOG)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_done = 1;
		close(STDIN_FILENO);
		big_stopping(SET, 1);
	}
	else
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	event_hook(void)
{
	rl_variable_bind("enable-bracketed-paste", "off");
	return (0);
}

void	handle_quit(int sig)
{
	(void)sig;
}

void	signaling(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_quit;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
