/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdeeznuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:11:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 10:26:15 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_deeznuts(t_bananas *bana, t_node *env)
{
    (void)env;
    token_cleaner(bana, 0);
    if (!bana->token[0])
    {
        ;
    }
    if(chdir(bana->token[0]))
        printf("cd: %s not set\n", bana->token[0]);
    if (bana->token[0])
        token_cleaner(bana, 0);
}
