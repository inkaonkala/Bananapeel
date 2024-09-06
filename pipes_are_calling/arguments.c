/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.f              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:16:47 by iniska            #+#    #+#             */
/*   Updated: 2024/05/09 10:17:01 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool parse_cmd_args(t_bananas *bana)
{
    int		i;
    char	**args;

    bana->cmd_args = ft_calloc(bana->tok_num, sizeof(char **));
    if (!bana->cmd_args)
        return (false);

    i = 0;
    while (i < bana->tok_num - 1)
    {
        args = ft_split(bana->token[i], ' ');
    
        if (!args)
        {
            free_char_array(&(bana->cmd_args), i);
            bana->cmd_args = NULL;
            return (false);
        }
        
        bana->cmd_args[i] = *args;
        i++;
    }
    bana->cmd_args[i] = NULL;
    return (true);
}
