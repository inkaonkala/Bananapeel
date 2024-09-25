/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:32:34 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/25 12:14:58 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	parsing(char *str, t_bananas *bana)
{
	char	**tokens;
	int		token_count;

	token_count = count_tokens(str);
	if (token_count == 0)
		return (true);
	free_char_array(bana->envp);
	bana->envp = list_to_eepie(&bana->env);
	tokens = ft_calloc((token_count + 1), sizeof(char *));
	if (!tokens)
		return (false);
	if (!extract_tokens(str, tokens, bana))
	{
		free_char_array(tokens);
		return (false);
	}
	if (!banananice(bana, tokens, token_count))
		return (true);
	command_search(bana, bana->envp, &bana->env);
	return (true);
}
