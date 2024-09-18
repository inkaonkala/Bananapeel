/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:53:11 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 10:10:17 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_s(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	_exit(1);
}

void	free_argh(char **argh)
{
	int	i;

	i = 0;
	while (argh[i])
	{
		free(argh[i]);
		i++;
	}
	free(argh);
}

void	shut_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
