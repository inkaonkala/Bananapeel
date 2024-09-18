/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:16:39 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 15:22:37 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	input_check(t_bananas *bana, int fd[2])
{
	bana->original_stdin = dup(STDIN_FILENO);
	if (bana->original_stdin == -1)
	{
		perror("Failed to duplicate STDIN\n");
		return (false);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (false);
	}
	return (true);
}

static bool	dog_loop(const char *delimiter, t_bananas *bana, int fd[2])
{
	char	*line;
	bool	stop;

	stop = false;
	while (1)
	{
		line = readline_wrapper("here_dog> ", bana);
		if (!line)
		{
			if (big_stopping(GET, 0))
				bana->heredog_interrupted = 1;
			else
				stop = true;
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	return (stop);
}

static void	closing_dog(t_bananas *bana, bool stop, const char *del, int fd[2])
{
	close(fd[1]);
	set_heredog_status(OUT_HEREDOG);
	if (bana->heredog_interrupted || stop)
	{
		close(fd[0]);
		if (stop)
		{
			printf("\nBananas: heredog delimited by end-of-file (wanted `%s')\n",
				del);
		}
	}
	else
	{
		bana->in_files[bana->infile_count] = fd[0];
		bana->infile_count++;
	}
}

void	handle_the_dog(const char *delimiter, t_bananas *bana)
{
	int		fd[2];
	bool	stop;

	if (!input_check(bana, fd))
		return ;
	bana->heredog_interrupted = 0;
	set_heredog_status(IN_HEREDOG);
	big_stopping(SET, 0);
	stop = dog_loop(delimiter, bana, fd);
	closing_dog(bana, stop, delimiter, fd);
	if (bana->original_stdin != -1)
	{
		dup2(bana->original_stdin, STDIN_FILENO);
		close(bana->original_stdin);
		bana->original_stdin = -1;
	}
}
