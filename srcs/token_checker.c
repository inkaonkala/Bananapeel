/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:41:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/05 18:10:39 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

static bool valid(t_bananas *bana, int j)
{
    if ((j < bana->tok_num) && 
        (ft_strncmp(bana->token[j], "|", 1) != 0) && 
        (ft_strncmp(bana->token[j], "<", 1) != 0) && 
        (ft_strncmp(bana->token[j], ">", 1) != 0))
        {
            if (bana->is_rdr)
            {
                if (ft_strncmp(bana->token[j], "echo\0", 5) != 0)
                    return (true);
                else
                    return (false);
            }
            return (true);
        }
    else
        return (false);
    
}

static void merge_it(t_bananas *bana, int i, int j)
{
	int		len;
	char	*new_str;

	if((ft_strncmp(bana->token[i], "<", 1)) == 0 || (ft_strncmp(bana->token[i], ">", 1) == 0))
		return ;
	len = ft_strlen(bana->token[i]) + ft_strlen(bana->token[j]) + 2;
    new_str = (char *)malloc(len * sizeof(char));
	if (new_str == NULL)
	{
		ft_printf("Malloc fail in merge\n");
		exiting(bana, 1);
    }
	ft_strlcpy(new_str, bana->token[i], len);
	ft_strlcat(new_str, " ", len);
	ft_strlcat(new_str, bana->token[j], len);
	free(bana->token[i]);
	bana->token[i] = new_str; 
	if (j < bana->tok_num && ((ft_strcmp(bana->token[i], "|") != 0) ||
	ft_strncmp(bana->token[i], "<", 1) != 0 ||
	ft_strncmp(bana->token[i], ">", 1) != 0 ||
	ft_strncmp(bana->token[i], "echo\0", 5) != 0))
    	token_cleaner(bana, j);
}

void    token_merge(t_bananas *bana)
{
    int i;
    int j;

    i = 0;
    while (i < bana->tok_num)
    {
        if (valid(bana, i))
        {
            j = i + 1;
            while (valid(bana, j))
				merge_it(bana, i, j);	
        }
        i++;

    }
}

void    command_search(t_bananas *bana, char **envp, t_node **env)
{
    if (!bana->is_rdr && !bana->is_pipe)
        built_ins(bana, env);
    
    del_quotes(bana);
    token_merge(bana);
	
    //del_quotes(bana);
    if (bana->is_dog)
    {
        big_stopping(SET, 0);
        while (bana->tok_num > 0)
            token_cleaner(bana, 0);
        return ;
    }
    if (bana->is_rdr && !bana->is_pipe)
	{
		file_malloc(bana);
        redirections(bana, envp, env);
	}
    if (bana->tok_num > 0)
        pipex(bana, envp, env);   
    
    while (bana->tok_num > 0)
        token_cleaner(bana, 0);
	
    if(bana->tok_num > 0)
        ft_printf(" You have tokens left to clean!\n");
	
}

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


