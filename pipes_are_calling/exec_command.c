/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/08/22 15:07:43 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	shut_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	execute_command(t_bananas *bana, char **envp, int index)
{

	if(bana->cmd_paths[index])
	{
			execve(bana->cmd_paths[index], &bana->cmd_args[index], envp);
			exit (1);
	}
	else
	{
		ft_printf("Bananas! Can't find your command :( \n"); // WHICH WE WANT TO USE?
		//perror("Bananas! Can't find your command: ");
		exit (1);
	}

}

bool	fork_it(t_bananas *bana, int fd[2], pid_t *pid, int index)
{
	if (index < bana->tok_num)
	{
		if(pipe(fd) == -1)
		{
			perror("No pipes to fork the banananas\n");
			return (false);
		}
	}

	*pid = fork();
	if (*pid == -1)
	{
		perror("I don't use fork to eat banananas\n");
		if (index < bana->tok_num)
			shut_fd(fd);
		return (false);
	}
	return (true);
}

int	create_child(t_bananas *bana, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];
	int		last;
	//int		first;

	last = (index == bana->tok_num);
	//first = (index == 0);

	if (!fork_it(bana, fd, &pid, index))
		return (false);
	

	if (pid == 0)
	{
		if(bana->is_rdr)
		{
			if(!redirect_file_input(bana))
				redirect_input(bana, index);
			redirect_file_putput(bana);
		}
		else
		{
			redirect_input(bana, index);
			redirect_putput(bana, fd, index);
		}
		execute_command(bana, envp, index);
	}
	else
	{
		if (index > 0)
			close(bana->prev_fd[0]);

		if (!last)
		{
			bana->prev_fd[0] = fd[0];
			close(fd[1]);
		}
	}
	return (true);
}
