/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:07:40 by iniska            #+#    #+#             */
/*   Updated: 2024/07/22 16:06:18 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char *add_n(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	str[i] = '\n';
	return (str);
}

char	*find_delimiter(char *str)
{
	int		i;
	int		len;
	char	*deli;
	int		start;

	start = 0;
	i = 0;
	len = 0;
	while(str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != '<')
			i++;
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while (str[i] == ' ')
				i++;
		
			start = i;
			while(str[i] != ' ' && str[i] != '\0')
				i++;
			len = i - start;

			deli = malloc(sizeof(char) * (len + 1));
			if(!deli)
			{
				perror("Malloc dogged");
				exit(EXIT_FAILURE);
			}
			ft_strlcpy(deli, &str[start], len + 1);
			add_n(deli);
			return (deli);
		}
		if(str[i] != '\0')
			i++;
	}
	return (NULL);
}


