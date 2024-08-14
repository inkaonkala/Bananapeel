#include "../minishell.h"

static t_node	*find_last(t_node	*stack)
{
	t_node	*temp;

    printf("inside find last\n");
	if (!stack)
		return (NULL);
	temp = stack;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = malloc(sizeof(char) * ft_strlen(str));
	if (!last)
		return (1);
	last->next = NULL;
    printf("inside add_end\n");
	ft_strlcpy(last->line, str, ft_strlen(str));
    printf("after strlcpy\n");
	if (!(*stack))
	{
        printf("inside add_end if\n");
		*stack = last;
		last->prev = NULL;
	}
	else
	{
        printf("inside add_end else\n");
		pre = find_last(*stack);
		pre->next = last;
		last->prev = pre;
	}
	return (0);
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
		free(curr);
		curr = temp;
	}
	*env = NULL;
}

static void load_list(char **envp, t_node **env)
{
    int i;

    i = 0;
    printf("Load_list\n");
    while (envp[i])
    {
        if (add_end(env, envp[i++]))
        {
            free_env(env);
            write(1, "Error\n", 6);
            exit(1);
        }
        ft_printf("another line\n");
    }

}



void    command_search(t_bananas *bana, char **envp)
{
    t_node   **env;
    int i;

    i = 0;
    while (envp[i])
    {
        i++;
    }
    env = (t_node **)malloc(sizeof(t_node) * (i + 1));
    load_list(envp, env);
    printf("command_search\n");
    if(bana->is_pipe)
        pipex(bana, envp);
    else if(bana->is_rdr)
        redirections(bana, envp);
    else
        built_ins(bana, env);



    //if(bana->token[0] != executable)
    //    free_tokens(bana);

    //else if(bana->is_dog && !bana->is_pipe)
    //    here_dog(bana);
}
