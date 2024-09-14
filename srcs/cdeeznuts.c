/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdeeznuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:11:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/14 17:23:29 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void homeward_bound(t_bananas *bana)
{   
    char *temp;

    temp = NULL;
    printf("homewardbound\n");
    while (bana->env)
    {
        if (!bana->env->next)
            break;
        if (!ft_strcmp(bana->env->key, "HOME"))
        {
            printf("home found\n");
            temp = bana->env->value;
            if(chdir(temp))
            {
                printf("home not found\n");
                exiting(bana, 1);
            }
            // exiting(bana, 1);
        }
        bana->env = bana->env->next;
    }
}

void handle_deeznuts(t_bananas *bana)
{
    token_cleaner(bana, 0);
    printf("this is bana->token[0]:  %s <- \n", bana->token[0]);
    printf("# of tokens:  %i <- \n", bana->tok_num);

    if (bana->token)
    {
        homeward_bound(bana);
         return ;
    }
    if(chdir(bana->token[0]))
    {
        printf("cd: %s not set\n", bana->token[0]);
        // return ;
    }
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
    printf("\nhere\n");
    // if (bana->token[1])
    //     printf("bana->token: %s\n", bana->token[1]);
    // if (bana->token[2])
    //     printf("bana->token: %s\n", bana->token[2]);

    
    if (bana->is_rdr)
		exit (0);
}