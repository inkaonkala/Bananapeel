/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:37:19 by iniska            #+#    #+#             */
/*   Updated: 2024/08/23 17:41:03 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n🍌banana_peel:", 17);
}

static void	handle_quit(int sig)
{
	(void)sig;
	if (get_heredog_status() == IN_HEREDOG)
		(void)sig; // heredog stuff
	else
		(void)sig; // normal stuff
}

void    signaling(void)
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

    sigemptyset(&sa_int.sa_mask); // these are ready functions from allowed externals
    sigemptyset(&sa_quit.sa_mask);

    //CTRL + C SIGINT, display new prompt

    sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART; // allowed this is?
	sigaction(SIGINT, &sa_int, NULL);


    //CTR + \ EOF, exit the program clean

	sa_quit.sa_handler = handle_quit;
	sa_quit.sa_flags = SA_RESTART; // Restarts interrupted system calls
	sigaction(SIGQUIT, &sa_quit, NULL);

    // CTR + Z SIGQUIT, does nothing
	
	signal(SIGTSTP, SIG_IGN); 
}

