/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/07/22 16:06:47 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_buffer(int pipefd)
{
	char 	*buffer;
	ssize_t	n;

	buffer = malloc(300); // THIS NEEDS TO BE MALLOCED CORRECTLY!
	if (!buffer)
	{
		perror("Malloc's bananas!\n");
		exit(EXIT_FAILURE);
	}
	while((n = read(pipefd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, n);
	free(buffer);
}

static void	signal_dog(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nI am giving you an error message\n", 30);
	exit(EXIT_FAILURE);
}
//create a pipe and use it as fd, remember to close after use, or may cause freeze
void	handle_the_dog(const char *delimiter)
{
    int     pipefd[2];
    pid_t   pid;
    char    *line;

    line = NULL;
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, signal_dog);
		close(pipefd[0]);

		while(1)
		{
			ft_printf("here_dog> ");
			line = readline(STDIN_FILENO); // should we use readline here?
			if ((line == NULL || strcmp(line, delimiter)) == 0)
			{
				ft_printf("Dog_exited!\n");
				free (line);
				break ;
			}
			//ft_printf("here_dog> ");
			write(pipefd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
		read_buffer(pipefd[0]);
		close(pipefd[0]);
	}
}

void	find_dog(char *str)
{       
	char *delimiter;

	delimiter = find_delimiter(str);
	handle_the_dog(delimiter);
	free(delimiter);
}
