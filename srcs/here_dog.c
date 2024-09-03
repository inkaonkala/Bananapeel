/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:19:18 by iniska            #+#    #+#             */
/*   Updated: 2024/09/03 16:48:38 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_the_dog(const char *delimiter, t_bananas *bana)
{
    char    *line;
	int		fd[2];
	
	pipe(fd); // check failure
	big_stopping(SET, 0);
	set_heredog_status(IN_HEREDOG);
    line = readline("here_dog> ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		ft_putendl_fd(line, fd[1]);
		free(line);
		if (big_stopping(GET, 1))
			break ;
		line = readline("here_dog> ");
	}
	close(fd[1]);
	bana->in_files[bana->infile_count] = fd[0];
	bana->infile_count++;
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
