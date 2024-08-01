#include "../minishell.h"

static bool	handle_commands(t_bananas *bana, char **envp)
{
	/*
	if (!check_arguments(bana))
	{
		//clean_n_errors(bana);
		return (false);
	}
	
	ft_printf("after check_arguments\n");

	*/

	if (!parse_cmd_line(bana, envp))
	{
		clean_n_errors(bana);
		return (false);
	}
	

	ft_printf("after parse_cmd_line\n");
	
	if (!parse_cmd_args(bana))
	{
		clean_n_errors(bana);
		return (false);
	}
	ft_printf("kooookookoo\n");
	

	return (true);
	
}

int	pipex(t_bananas *bana, char **envp)
{
	int		    i;

	init_pipes(bana);

	if (!handle_commands(bana, envp))
	{
		ft_printf("Bananas! Commands failed\n");
		return (-1);
	}

	
	i = -1;
	while (i++ < bana->tok_num)
	{
		if (!create_child(bana, envp, i))
			break ;
	}
	
	i = 0;
	while (i < bana->tok_num - 1)
	{
		close(bana->fd_input);
		close(bana->fd_output);
		i++;
	}
	
	i = -1;
	while (i++ < bana->tok_num)
		wait(NULL);
	
	close(bana->fd_input);
	close(bana->fd_output);
	
	return(0);
}

