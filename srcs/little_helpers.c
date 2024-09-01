/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:42:49 by iniska            #+#    #+#             */
/*   Updated: 2024/09/01 13:33:42 by jbremser         ###   ########.fr       */
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

int    quote_chk(char *str, char *cur_quo, int i)
{
    int quotes = 0;
    char quote_char = '\0';

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            if (quotes && str[i] == quote_char)
                quotes = 0;
            else if (!quotes && (str[i] == '"' || str[i] == '\''))
            {
                quotes = 1;
                quote_char = str[i];
                *cur_quo = str[i];
            }
        }
        i++;
    }
    if (quotes)
    {
        while (str[i])
            i++;
    }
    return i;
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
