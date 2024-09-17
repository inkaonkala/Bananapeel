/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/17 09:43:03 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_the_dog(const char *delimiter, t_bananas *bana)
{
    char    *line;
	int		fd[2];
	bool	EOF_encountered;
	
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
	big_stopping(SET, 0);
	while (1)
	{
		line = readline_wrapper("here_dog> ", bana);
		if (!line)
		{
			if(big_stopping(GET, 0))
				bana->heredog_interrupted = 1;
			else
				EOF_encountered = true;
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		ft_putendl_fd(line,fd[1]);
		free(line);
	}
	close(fd[1]);
	set_heredog_status(OUT_HEREDOG);
	if (bana->heredog_interrupted || EOF_encountered)
	{
		close(fd[0]);
		if (EOF_encountered)
		{
			printf("\nbanana: warning: heredog delimited by end-of-file (wanted `%s')\n", 
            delimiter);
		}
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
}

int big_stopping(int get, int newvalue)
{
	static int	stopper = 0;

	if (get)
		return stopper;
	else
		stopper = newvalue;
	return stopper;
}

static char	*clean_deli(char *str)
{
	char *copy;

	int i;

	i = 0;
	copy = malloc(sizeof(char) * 4);
	if(!copy)
	{
		ft_printf("Malloc fail in dog\n");
		return (0);
	}
	while(str[i] == '<' && str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
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
	{
		delimiter = bana->token[tk_i] + 2;
		bana->token[tk_i] = clean_deli(bana->token[tk_i]);
	}
	//ft_printf("THIS IS :%s\n", delimiter);
	handle_the_dog(delimiter, bana);
	if (separate)
		free(delimiter);
}

char	*readline_wrapper(const char *prompt, t_bananas *bana)
{
	char *line;

	line = readline(prompt);
	if (big_stopping(GET, 0))
	{

		free(line);
		bana->heredog_interrupted = 1;
		return (NULL);
	}
	return (line);
}
