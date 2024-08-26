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
	while(bana->tok_num > 0)
		token_cleaner(bana, 0);
}

/*
int	pipex(t_bananas *bana, char **envp)
{
	int		    i;

	init_pipes(bana);

	if (!handle_commands(bana, envp))
	{
		ft_printf("Bananas! Commands failed\n");
		return (-1);
	}

	
	i = 0;
	while (i < bana->tok_num)
	{
		if (!create_child(bana, envp, i))
			break ;
		i++;
	}
	
	i = 0;
	while (i < bana->tok_num - 1)
	{
		close(bana->pipes[i][0]);					//close(bana->fd_input);
		close(bana->pipes[i][1]);					//close(bana->fd_output);
		i++;
	}
	
	i = -1;
	while (i++ < bana->tok_num)
		wait(NULL);
	
	//if(bana->has_input)
	//{
	//	close(bana->fd_input);
	//	close(bana->fd_output);
	//}

	return(0);
}
*/

