/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:52:33 by jbremser          #+#    #+#             */
/*   Updated: 2024/04/12 12:25:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freenull(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*line_read(int fd, char	*stash, t_gnl *gnl)
{
	gnl->bytes_read = 1;
	while (!ft_strchr(stash, '\n') && gnl->bytes_read != 0)
	{
		gnl->bytes_read = read(fd, gnl->buffer, BUFFER_SIZE);
		if (gnl->bytes_read == 0 || gnl->bytes_read == -1)
		{
			if (gnl->bytes_read == 0)
				return (stash);
			if (gnl->bytes_read == -1)
				freenull (&stash);
			return (NULL);
		}
		gnl->buffer[gnl->bytes_read] = '\0';
		if (!stash)
		{
			stash = malloc(1);
			if (!stash)
				return (NULL);
			stash[0] = '\0';
		}
		gnl->temp = stash;
		stash = ft_strjoin(stash, gnl->buffer);
		freenull(&(gnl->temp));
	}
	return (stash);
}

static char	*trimprefix(char *stash, t_gnl *gnl)
{
	if (!stash)
		return (NULL);
	gnl->i = 0;
	while (stash[gnl->i] != '\n' && stash[gnl->i] != '\0')
		gnl->i++;
	if (stash[gnl->i] == '\n')
		gnl->i++;
	gnl->line = malloc(gnl->i + 1);
	if (gnl->line == NULL)
		return (NULL);
	gnl->i = 0;
	while (stash[gnl->i] != '\n' && stash[gnl->i] != '\0')
	{
		gnl->line[gnl->i] = stash[gnl->i];
		gnl->i++;
	}
	if (stash[gnl->i] == '\n')
	{
		gnl->line[gnl->i] = stash[gnl->i];
		gnl->i++;
	}
	gnl->line[gnl->i] = '\0';
	return (gnl->line);
}

static char	*trimstash(char	*stash, t_gnl *gnl)
{
	if (!gnl->line
		|| !(ft_strchr(stash, '\n'))
		|| (ft_strchr(stash, '\n') && ft_strlen(ft_strchr(stash, '\n')) == 1))
	{
		freenull (&stash);
		return (NULL);
	}
	gnl->i = 0;
	while (stash[gnl->i] != '\n' && stash[gnl->i] != '\0')
		gnl->i++;
	if (stash[gnl->i] == '\n')
		gnl->i++;
	gnl->temp = stash;
	stash = ft_substr(stash, gnl->i, ft_strlen(stash));
	freenull (&(gnl->temp));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	t_gnl		gnl;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.temp = NULL;
	if (!ft_strchr(stash, '\n'))
	{
		gnl.buffer = malloc(BUFFER_SIZE + 1);
		if (!gnl.buffer)
		{
			if (stash != NULL)
				freenull(&stash);
			return (NULL);
		}
		stash = line_read(fd, stash, &gnl);
		freenull(&(gnl.buffer));
	}
	gnl.line = trimprefix(stash, &gnl);
	stash = trimstash(stash, &gnl);
	return (gnl.line);
}
