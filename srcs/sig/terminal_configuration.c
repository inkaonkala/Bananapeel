/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:03 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/20 11:23:06 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_terminal(struct termios *original_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, original_termios);
	new_termios = *original_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	restore_terminal(const struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
