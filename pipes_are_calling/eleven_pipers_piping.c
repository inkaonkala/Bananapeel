/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eleven_pipers_piping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:01:35 by iniska            #+#    #+#             */
/*   Updated: 2024/09/03 11:01:40 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_commands(t_bananas *bana, char **envp, t_node **env)
{
	if(bana->is_rdr)
	{
		redirections(bana, envp, env);
		//ft_printf("		OUT_FD %d\n", bana->out_files[bana->outfile_count - 1]);
	}
  
	if (!parse_cmd_line(bana, envp))
	{
		clean_n_errors(bana);
		return (false);
	}

	if (!parse_cmd_args(bana))
	{
		clean_n_errors(bana);
		return (false);
	}
	//ft_printf("					Parsing for pipes, DONE!\n");
	return (true);
}

void pipex(t_bananas *bana, char **envp, t_node **env)
{
    int i;
    pid_t pid;

    bana->prev_fd[0] = -1;
    bana->prev_fd[1] = -1;

    if (!handle_commands(bana, envp, env))
    {
        ft_printf("Bananas! Commands failed\n");
        return ;
    }

    i = 0;
    while (i < bana->tok_num)
    {
        if (!create_child(bana, envp, i))
            return ;
        i++;
    }

    i = 0;
    while (i < bana->tok_num)
    {
        waitpid(-1, NULL, 0);
        i++;
    }
}


