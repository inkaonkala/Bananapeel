/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:37:19 by iniska            #+#    #+#             */
/*   Updated: 2024/08/05 13:38:04 by iniska           ###   ########.fr       */
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
