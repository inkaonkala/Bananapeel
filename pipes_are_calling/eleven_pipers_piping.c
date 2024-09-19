/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eleven_pipers_piping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:01:35 by iniska            #+#    #+#             */
/*   Updated: 2024/09/19 17:13:40 by jbremser         ###   ########.fr       */
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

bool	rdr_in_pipes(t_bananas *bana, char **envp)
{	
	bana->rdr_in_pipe = true;
	redirections(bana, envp);
	if (bana->tok_num > 0)
	{
		while (strncmp(bana->token[0], "|", 1) != 0)
			token_cleaner(bana, 0);
		token_cleaner(bana, 0);
		bana->is_rdr = false;
		return (true);
	}
	return (false);
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
