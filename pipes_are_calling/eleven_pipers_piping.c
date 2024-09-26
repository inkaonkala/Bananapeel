/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eleven_pipers_piping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:01:35 by iniska            #+#    #+#             */
/*   Updated: 2024/09/26 13:26:43 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	waiting(int i, int *status)
{
	waitpid(-1, status, 0);
	i++;
	return (i);
}

static bool	handle_commands(t_bananas *bana, char **envp, t_node **env)
{	
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
	if (bana->is_rdr)
		redirections(bana, envp);
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
	return (true);
}

void	pipex(t_bananas *bana, char **envp, t_node **env)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	if (!handle_commands(bana, envp, env))
	{
		clean_struct(bana);
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
		i = waiting(i, &status);
	if (WIFEXITED(status))
		bana->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		bana->last_exit_status = 128 + WTERMSIG(status);
}

void	eleven_pipers(t_bananas *bana, char **envp, t_node **env)
{
	if (bana->is_rdr)
	{
		if (rdr_in_pipes(bana, envp))
		{
			if (bana->tok_num > 0)
				pipex(bana, envp, env);
		}
	}
	else
		pipex(bana, envp, env);
}
