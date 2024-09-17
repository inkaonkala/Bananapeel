/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broom_n_vacuum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:23:36 by iniska            #+#    #+#             */
/*   Updated: 2024/09/17 11:16:53 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

static void clean_files(t_bananas *bana)
{
	int i; 
	
	i = 0;
	if (bana->in_files != NULL)
	{
		free(bana->in_files);
		bana->in_files = NULL;
	}
	if(bana->out_files != NULL)
	{
		free(bana->out_files);
		bana->out_files = NULL;
	}
	if(bana->cmd_paths != NULL)
	{
		while(bana->cmd_paths[i] != NULL)
		{
			free(bana->cmd_paths[i]);
			bana->cmd_paths[i] = NULL;
			i++;
		}
		free(bana->cmd_paths);
		bana->cmd_paths = NULL;
	}
}

void	clean_struct(t_bananas *bana)
{
	while (bana->tok_num > 0)
		token_cleaner(bana, 0);
	clean_files(bana);
	if(bana->pipes != NULL)
	{
		free(bana->pipes);
		bana->pipes = NULL;
	}
	bana->tok_num = 0;
	bana->infile_count = 0;
	bana->outfile_count = 0;
	bana->fd_input = -1;
	bana->fd_output = -1;
	bana->prev_fd[0] = -1;
	bana->prev_fd[1] = -1;
}

void	free_stuff(char **args, char *path)
{
	int	i;

	i = 0;
	while(args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	if (path)
		free(path);
}

void token_cleaner(t_bananas *bana, int i)
{
    if (bana->token == NULL || i >= bana->tok_num)
        return;  
    free(bana->token[i]);
	while (i < bana->tok_num - 1) 
	{
        bana->token[i] = bana->token[i + 1];
        i++;
    }
    bana->token[bana->tok_num - 1] = NULL;
    bana->tok_num--;
    if (bana->tok_num == 0) 
	{
        free(bana->token);
        bana->token = NULL;
    }
}

void    exiting(t_bananas *bana, int i)
{
	clean_banana(bana);
	exit(i);
    // If something else to clean, clean here mebbe?
}

void	free_env(t_node	**env)
{
	t_node	*temp;
	t_node	*curr;

   
	curr = *env;
	temp = NULL;
	while (curr)
	{
		temp = curr->next;
		free(curr->value);
		free(curr->key);
		free(curr);
		curr = temp;
	}
	*env = NULL;
}

void clean_banana(t_bananas *bana)
{
	clean_struct(bana);
	free_env(&bana->env);
	free_char_array(bana->envp);
}

void	free_array(char ***paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(*paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (*paths[i] != NULL)
				free((*paths[i]));
			i++;
		}
	}
	free (*paths);
	*paths = NULL;
}

void	free_line(char **paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free(paths[i]);
			i++;
		}
	}
	free(paths);
	paths = NULL;
}

char    *free_char_array(char **array)
{
    size_t    i;

    if (array == NULL)
        return (NULL);
    i = 0;
    while ((array)[i] != NULL)
    {
        free((array)[i]);
        (array)[i] = NULL;
        i++;
    }
    // *array = NULL;
    free(array);
    return (NULL);
}

void	clean_n_errors(t_bananas *bana)
{
	if (bana->fd_input != -1)
		close(bana->fd_input);
	if (bana->fd_output != -1)
		close(bana->fd_output);
	if (bana->cmd_paths != NULL)
		free_line(bana->cmd_paths, bana->tok_num - 1);
	if (bana->token != NULL)
		free_array(&bana->token, bana->tok_num - 1);
	free(bana);
}

// void	free_char_array(char **paths)
// {
// 	int i;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		free(paths[i]);
// 		paths[i] = NULL;
// 		i++;
// 	} 
// 	free(paths);

// }

// void token_cleaner(t_bananas *bana, int i)
// {
// 	free(bana->token[i]);
// 	while (i < bana->tok_num - 1)
// 	{
// 		printf("\ninside\n");
// 		bana->token[i] = bana->token[i + 1];
// 		i++;	
// 	}
// 	bana->tok_num--;
//     bana->token[bana->tok_num] = NULL;
// 	if (bana->tok_num == 0)
// 		free(bana->token);
// }
