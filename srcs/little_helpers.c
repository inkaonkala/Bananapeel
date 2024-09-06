/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/09/05 18:39:55 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	free_stuff(char **args, char *path)
{
	int	i;

	i = 0;
	while(args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	if (path)
		free(path);
}

int	empties(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int    	quote_chk(char *str, char *cur_quo, int i)
{
    int quotes;

    quotes = 0;
    while (str[i] && (!empties(str[i]) || quotes))
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			if (quotes && str[i] == *cur_quo)
				quotes = 0;
			else if (!quotes)
			{
				quotes = 1;
				*cur_quo = str[i];
			}
		}
	    i++;			
    }
    return (i);
}


bool	check_specials(char *token)
{
	if (ft_strcmp(token, "|") == 0 
		|| ft_strcmp(token, ">") == 0 
			|| ft_strcmp(token, ">>") == 0)
		return (true);	
	return (false);
}

int	number_checker(char *argv)
{
	size_t i;

	i = 0;
	while (i <= ft_strlen(argv) - 1)
	{
		if (ft_isdigit(argv[i]) == 1)
			return (1);
		i++;	
	}
	return (0);

}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}


	// int	num;
	// int	temp;

	// printf("inside number_checker\n");
	// num = ft_atoi(argv);
	// temp = 0;
	// if (num < 0)
	// 	return (1);
	// if (num == 0)
	// 	return (0);
	// while (num > 0)
	// {
	// 	temp = num % 10;
	// 	if (temp < 0 || temp > 9)
	// 		return (1);
	// 	num /= 10;
	// }
	// return (0);
