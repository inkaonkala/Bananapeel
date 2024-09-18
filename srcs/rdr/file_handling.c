/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:06:52 by iniska            #+#    #+#             */
/*   Updated: 2024/09/18 13:47:35 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*clean_arrows(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
	{
		ft_printf("Malloc fail in arrows");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		while (str[i] == '<' || str[i] == '>')
			i++;
		while (str[i] != '\0')
		{
			copy[j] = str[i];
			i++;
			j++;
		}
	}
	copy[j] = '\0';
	return (copy);
}

static void	to_files(t_bananas *bana, int i)
{
	bool	append;

	if (ft_strncmp(bana->token[i], ">>", 2) == 0)
	{
		append = true;
		if (ft_strncmp(bana->token[i], ">>\0", 3) != 0)
			bana->token[i] = clean_arrows(bana->token[i]);
		else
			token_cleaner(bana, i);
		open_outfile(bana, i, append);
		token_cleaner(bana, i);
	}	
	else if (ft_strncmp(bana->token[i], ">", 1) == 0)
	{
		append = false;
		if (ft_strncmp(bana->token[i], ">\0", 2) != 0)
			bana->token[i] = clean_arrows(bana->token[i]);
		else
			token_cleaner(bana, i);
		open_outfile(bana, i, append);
		token_cleaner(bana, i);
	}
}

static void	from_files(t_bananas *bana, int i)
{
	if (ft_strncmp(bana->token[i], "<<", 2) == 0)
		bana->token[i] = clean_arrows(bana->token[i]);
	else if (ft_strncmp(bana->token[i], "<", 1) == 0)
	{
		if (ft_strncmp(bana->token[i], "<\0", 2) != 0)
			bana->token[i] = clean_arrows(bana->token[i]);
		else
			token_cleaner(bana, i);
		open_infile(bana, i);
		token_cleaner(bana, i);
	}
}

void	file_handling(t_bananas *bana)
{
	int	i;

	i = 0;
	while (bana->token[i] && bana->tok_num > 1)
	{
		if (ft_strncmp(bana->token[i], "<", 1) == 0)
			from_files(bana, i);
		else if (ft_strncmp(bana->token[i], ">", 1) == 0)
			to_files(bana, i);
		else
			i++;
	}
}
