/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/05 13:01:38 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_the_dog(const char *delimiter, t_bananas *bana)
{
    char    			*line;
	int					fd[2];
	
	dprintf(2, "DEBUG: Entering handle_the_dog, delimiter: %s\n", delimiter);
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
	dprintf(2, "DEBUG: Set heredog status to IN_HEREDOG\n");
	while (1)
	{
		line = readline_wrapper("here_dog> ", bana);
		if (!line || bana->heredog_interrupted)
		{
			dprintf(2, "DEBUG: Heredoc interrupted or EOF reached\n");
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			dprintf(2, "DEBUG: Delimiter matched, exiting heredoc\n");
			free (line);
			break ;
		}
		ft_putendl_fd(line,fd[1]);
		free(line);
	}
	close(fd[1]);
	set_heredog_status(OUT_HEREDOG);
	 dprintf(2, "DEBUG: Set heredog status to OUT_HEREDOG\n");
	if (bana->heredog_interrupted) // DEBUGGING WHY IT DOESN'T GOE HERE?????
	{
		close(fd[0]);
		dprintf(2, "DEBUG: Heredoc was interrupted\n");
		bana->is_valid_heredog_intake = false;
	}
	else
	{
		bana->in_files[bana->infile_count] = fd[0];
		bana->infile_count++;
		dprintf(2, "DEBUG: Heredoc completed successfully WHY DOES IT GOE HEEEERRRREEEE\n");
		bana->is_valid_heredog_intake = true;
	}
	if (bana->original_stdin != -1)
	{
		dup2(bana->original_stdin, STDIN_FILENO);
		close(bana->original_stdin);
		bana->original_stdin = -1;
		dprintf(2, "DEBUG: Restored original stdin\n");
	}
	dprintf(2, "DEBUG: Exiting handle_the_dog, is_valid_intake: %d\n", bana->is_valid_heredog_intake);

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

//int big_stopping(int get, int newvalue)
//{
//	static int	stopper = 0;
//
//	dprintf(2, "big stopping\n");
//	if (get)
//		return stopper;
//	else
//		stopper = newvalue;
//	return stopper;
//}

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
