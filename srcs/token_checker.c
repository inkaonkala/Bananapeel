/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:41:54 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/12 14:36:28 by etaattol         ###   ########.fr       */
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
    new_str = (char *)ft_calloc(len, sizeof(char));
	if (new_str == NULL)
	{
		ft_printf("Calloc fail in merge\n");
		cleanup_and_exit(bana, 1);
    }
	ft_strlcpy(new_str, bana->token[i], len);
	ft_strlcat(new_str, " ", len);
	ft_strlcat(new_str, bana->token[j], len);
	free(bana->token[i]);
	bana->token[i] = new_str; 
	if (j < bana->tok_num && ((ft_strcmp(bana->token[i], "|") != 0) ||
	ft_strncmp(bana->token[i], "<", 1) != 0 ||
	ft_strncmp(bana->token[i], ">", 1) != 0 ||
	ft_strncmp(bana->token[i], "echo", 4) != 0))
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
    
    token_merge(bana);

    if (bana->is_dog)
        big_stopping(SET, 0);
    
    if (bana->is_rdr && !bana->is_pipe)
        redirections(bana, envp, env);
    
    if (bana->tok_num > 0)
        pipex(bana, envp, env);   
    
    clean_struct(bana);	
}
