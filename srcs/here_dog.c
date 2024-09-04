/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/04 11:39:13 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_the_dog(const char *delimiter, t_bananas *bana)
{
    char    *line;
	int		fd[2];
	
	bana->original_stdin = dup(STDIN_FILENO);
	if (bana->original_stdin == -1)
	{
		perror("Failed to duplicate STDIN\n");
		return ;
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	bana->heredog_interrupted = 0;
	set_heredog_status(IN_HEREDOG);
	while (1)
	{
		line = readline("here_dog> ");
		if (!line || bana->heredog_interrupted)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		ft_putendl_fd(line,fd[1]);
		free(line);
	}
	if (bana->heredog_interrupted)
	{
		close(fd[0]);
		dprintf(2, "Heredog was interrrupted\n");
		return (1);
		//bana->skip_command = 1;
	}
	else
	{
		bana->in_files[bana->infile_count] = fd[0];
		bana->infile_count++;
	}
	if (bana->original_stdin != -1)
	{
		dup2(bana->original_stdin, STDIN_FILENO);
		close(bana->original_stdin);
		bana->original_stdin = -1;
	}

	return (0);
	//pipe(fd); // check failure
	//big_stopping(SET, 0);
	//set_heredog_status(IN_HEREDOG);
    //line = readline("here_dog> ");
	//while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	//{
	//	ft_putendl_fd(line, fd[1]);
	//	free(line);
	//	if (big_stopping(GET, 1))
	//		break ;
	//	line = readline("here_dog> ");
	//}
	//close(fd[1]);
	//bana->in_files[bana->infile_count] = fd[0];
	//bana->infile_count++;
}

int big_stopping(int get, int newvalue)
{
	static int	stopper = 0;

	dprintf(2, "big stopping\n");
	if (get)
		return stopper;
	else
		stopper = newvalue;
	return stopper;
}

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
	handle_the_dog(delimiter, bana);
	if (separate)
		free(delimiter);
}

char	*readline_wrapper(const char *prompt, t_bananas *bana)
{
	char *line;

	line = readline(prompt);
	if (bana->heredog_interrupted)
	{

		free(line);
		return (NULL);
	}
	return (line);
}