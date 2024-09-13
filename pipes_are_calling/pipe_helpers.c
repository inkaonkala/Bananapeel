/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:53:11 by iniska            #+#    #+#             */
/*   Updated: 2024/09/13 09:44:51 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void empty_prompt(void)
{
	char	*line;
	int		fd[2];

	signal(SIGINT, handle_sigint_s);
	if (pipe(fd) == -1)
	{
		perror("Bananas! Pipe creation failed");
		return ;
	}
	line = readline("");
	while (line)
	{
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("");
	}
	close(fd[1]);
	signal(SIGINT, SIG_DFL);
}

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
