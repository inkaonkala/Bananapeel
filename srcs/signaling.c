/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:37:19 by iniska            #+#    #+#             */
/*   Updated: 2024/09/05 12:52:11 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	if (get_heredog_status() == IN_HEREDOG)
	{
		dprintf(2, "DEBUG: SIGINT received during heredoc\n");
		write(STDOUT_FILENO, "^C\n", 3);
		rl_done = 1;
		close(STDIN_FILENO);
		//big_stopping(SET, 1);
		dprintf(2, "DEBUG: Closed STDIN_FILENO\n");
	}
	else
	{
		dprintf(2, "DEBUG: SIGINT received outside heredoc\n");
		write(STDOUT_FILENO, "\n", 1);
		//write(STDOUT_FILENO, "^C\n", 3);
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

static void	handle_quit(int sig)
{
	(void)sig;
	//if (get_heredog_status() == IN_HEREDOG)
	//	(void)sig; // heredog stuff
	//else
	//	(void)sig; // normal stuff
}

void    signaling(void)
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

    sigemptyset(&sa_int.sa_mask); // these are ready functions from allowed externals
    sigemptyset(&sa_quit.sa_mask);

    //CTRL + C SIGINT, display new prompt

    sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);


    //CTR + \ EOF, exit the program clean

	sa_quit.sa_handler = handle_quit;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);

    // CTR + Z SIGQUIT, does nothing
	
	//signal(SIGTSTP, SIG_IGN); 
}
/*
void	reset_terminal_settings(void)
{
	struct
}
*/