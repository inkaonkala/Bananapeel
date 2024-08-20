/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/08/20 17:38:38 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	_dprint(const int fd)
{
	const char	*line;

	ft_printf("heredoc:\n\n");
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free((void *)line);
		line = get_next_line(fd);
	}
}

//create a pipe and use it as fd, remember to close after use, or may cause freeze
void	handle_the_dog(const char *delimiter)
{
    char    *line;
	int		fd[2];

	pipe(fd); // check failuer
    line = readline("here_dog > ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) != 0))
	{
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("here_dog > ");
	}
	close(fd[1]);
	_dprint(fd[0]);
//	return (fd[0]);
}

//static void	read_buffer(int pipefd)
//{
//	char 	*buffer;
//	ssize_t	n;
//
//	buffer = malloc(300); // THIS NEEDS TO BE MALLOCED CORRECTLY!
//	if (!buffer)
//	{
//		perror("Malloc's bananas!\n");
//		exit(EXIT_FAILURE);
//	}
//	while((n = read(pipefd, buffer, sizeof(buffer))) > 0)
//		write(STDOUT_FILENO, buffer, n);
//	free(buffer);
//}
//
//static void	signal_dog(int sig)
//{
//	(void)sig;
//	write(STDOUT_FILENO, "\nI am giving you an error message\n", 30);
//	exit(EXIT_FAILURE);
//}
//
//

//void	handle_the_dog(const char *delimiter)
//{
//    int     pipefd[2];
//    pid_t   pid;
//    char    *line;
//
//    line = NULL;
//	if(pipe(pipefd) == -1)
//	{
//		perror("pipe");
//		exit(EXIT_FAILURE);
//	}
//	pid = fork();
//	if (pid == -1)
//	{
//		perror("fork");
//		exit(EXIT_FAILURE);
//	}
//	if (pid == 0)
//	{
//		signal(SIGINT, signal_dog);
//		close(pipefd[0]);
//
//		while(1)
//		{
//			ft_printf("here_dog> ");
//			line = readline(STDIN_FILENO); // should we use readline here?
//			if ((line == NULL || strcmp(line, delimiter)) == 0)
//			{
//				ft_printf("Dog_exited!\n");
//				free (line);
//				break ;
//			}
//			//ft_printf("here_dog> ");
//			write(pipefd[1], line, ft_strlen(line));
//			free(line);
//		}
//		close(pipefd[1]);
//		exit(EXIT_SUCCESS);
//	}
//	else
//	{
//		close(pipefd[1]);
//		wait(NULL);
//		read_buffer(pipefd[0]);
//		close(pipefd[0]);
//	}
//}
//

void	find_dog(t_bananas *bana, int tk_i)
{       
	char *delimiter;
	char	separate;

	separate = 0;
	if (ft_strlen(bana->token[tk_i]) == 2)
	{
		delimiter = find_delimiter(bana);
		separate = 1;
	}
	else
		delimiter = bana->token[tk_i] + 2;
	ft_printf("THIS IS :%s\n", delimiter);
	handle_the_dog(delimiter);
	if (separate)
		free(delimiter);
}
/*

void	find_dog(char *str)
{       
	char *delimiter;

	delimiter = find_delimiter(str);
	handle_the_dog(delimiter);
	free(delimiter);
}
*/
