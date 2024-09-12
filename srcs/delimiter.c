/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:07:40 by iniska            #+#    #+#             */
/*   Updated: 2024/09/11 18:21:04 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
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
*/

char	*find_delimiter(t_bananas *bana)
{
	int		i;
	int		len;
	char 	*deli;

	i = 0;
	//len = 5; unnecessary?
	while(bana->token[i])
	{
		if (!ft_strcmp(bana->token[i++], "<<"))
		{
			if (!bana->token[i])
				return (ft_strdup(""));
			//token_cleaner(bana, i);   token cleaning removed cause it changed the index
			len = ft_strlen(bana->token[i]);
			deli = malloc(sizeof(char) * (len  + 1));
			if(!deli)
			{
				clean_struct(bana); // THIS HERE?
				return (NULL);
			}
			ft_strlcpy(deli, bana->token[i], len + 1);
			token_cleaner(bana, i); //        token cleaning removed cause it changed the index
			return(deli);
		}
	}
	return (NULL);
}

/*
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
			//add_n(deli);
			//add_n(deli);
			return (deli);
		}
		if(str[i] != '\0')
			i++;
	}
	return (NULL);
}

*/
