/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/17 09:42:43 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	exit_coder(char *argv)
{
	size_t			i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (argv[i] != '\0')
	{
		if (!isdigit(argv[i]))
			return (0);
		i++;
	}
	i = 0;
	while (argv[i] != '\0')
	{
		if (result > (unsigned long)(INT_MAX / 10) ||
			(result == (unsigned long)(INT_MAX / 10) &&
				(argv[i] - '0') > (INT_MAX % 10)))
			result = result % ((unsigned long)INT_MAX + 1);
		result = result * 10 + (argv[i] - '0');
		i++;
	}
	return (result % 256);
}

static void	exiter(t_bananas *bana)
{
	int	temp;
	{
		if (number_checker(bana->token[1]))
		{
			temp = exit_coder(bana->token[1]);
			ft_printf("🍌Bye Bye BaNaNaNas🍌!\nexit(%d)\n", temp);
			while (bana->tok_num > 0)
				token_cleaner(bana, 0);
			clean_banana(bana);
			exit(temp);
		}
		else
		{
			(void)temp;
			ft_printf("🍌Bye Bye BaNaNaNas🍌!\nexit\n%s: %s: count your 🍌s!\n",
				bana->token[0], bana->token[1]);
			while (bana->tok_num > 0)
				token_cleaner(bana, 2);
			clean_banana(bana);
			exit(0);
		}
	}
}

void	handle_exit(t_bananas *bana)
{
	if (bana->tok_num == 1)
	{
		ft_printf("Bye Bye BaNaNaNas!\nexit\n");
		token_cleaner(bana, 0);
		clean_banana(bana);
		exit(0);
	}
	else if (bana->tok_num >= 2)
		exiter(bana);
}
