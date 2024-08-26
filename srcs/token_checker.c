/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:41:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/26 14:39:14 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// static void print_stack(t_node *stack)
// {

// 	t_node *ptr;
// 	ptr = stack;

// 	while (ptr)
// 	{
// 		ft_printf("%s\n", ptr->line);
// 		ptr = ptr->next;
// 	}
// }

void    token_merge(t_bananas *bana)
{
    bana->token[0] = bana->token[0];
    return ;
}
/*
static bool valid(t_bananas *bana, int j)
{
    if ((j < bana->tok_num) && 
        (ft_strcmp(bana->token[j], "|") != 0) && 
        (ft_strcmp(bana->token[j], "<") != 0) && 
        (ft_strcmp(bana->token[j], ">") != 0) && 
        (ft_strncmp(bana->token[j], "echo\0", 5) != 0))
       return (true);
    else
        return (false);
    
}
*/

/*
void    token_merge(t_bananas *bana)
{
    int i;
    int j;
    int len;

    i = 0;
    while (i < bana->tok_num)
    {
        if (valid(bana, i))
        {
            j = i + 1;
            //return ;
            while (valid(bana, j))
            {
                len = ft_strlen(bana->token[i] + ft_strlen(bana->token[j] + 2));
                bana->token[i] = realloc(bana->token[i], len);
                strcat(bana->token[i], " ");
                strcat(bana->token[i], bana->token[j]);
                if (j < bana->tok_num && (ft_strcmp(bana->token[i], "|") != 0) && (ft_strcmp(bana->token[i], "<") != 0) && (ft_strcmp(bana->token[i], ">") != 0) && (ft_strncmp(bana->token[i], "echo\0", 5) != 0))
                    token_cleaner(bana, j);
                continue;
            }
            
        }
        i++;

    }
    i = 0;
    while (i < bana->tok_num)
    {
        ft_printf("     %s\n", bana->token[i]);
        i++;
    }
    //num = find_num(bana, "|");
    

   // Go through the tokens 
   //     merge token[i] and i++ together in to token[i]
   //     untill | or < or > is found
   //     token_cleaner(bana, token[i---])

}
*/

void    command_search(t_bananas *bana, char **envp, t_node **env)
{
    if(!bana->is_rdr)
        built_ins(bana, env);

    //token_merge(bana);

    if(bana->is_rdr && !bana->is_pipe)
        redirections(bana, envp, env);
    
    
    if(bana->tok_num > 0)
        pipex(bana, envp, env);
    
    // CHECKER!
    if(bana->tok_num > 0)
        ft_printf(" You have tokens left to clean!\n");
}
    // int i;

    // i = 0;
    // printf("command_search\n");
    //if(bana->is_pipe)
    //    pipex(bana, envp);
    // while (env)
    // {
    //     printf("before print stack\n");
    //     print_stack(env[i]);
    //     i++;
    // }



    //if(bana->token[0] != executable)
    //    free_tokens(bana);

    //else if(bana->is_dog && !bana->is_pipe)
    //    here_dog(bana);
