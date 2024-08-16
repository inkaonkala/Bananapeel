#include "../minishell.h"

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

static t_node	*find_last(t_node	*stack)
{
	t_node	*temp;

	if (!stack)
		return (NULL);
	temp = stack;
	while (temp->next)
		temp = temp->next;
    // printf("inside find last\n");
	return (temp);
}

static t_node   *parse_str(t_node *node, char *str)
{
    char *split;
    int i;

    i = 0;    
    split = ft_strchr(str, '=');
    // split++;
    if (!split)
    {
        ft_printf("no split\n");
        node->value = NULL;
        node->key = ft_strdup(str);
    }
    else
    {
        i = split - str;
        // ft_printf("i: %d\n", i);
        split++;
        node->value = ft_strdup(split);
        // ft_printf("value: %s\n", node->value);
        // free(split);
        str[i] = '\0';
        node->key = ft_strdup(str);
        // ft_strlcpy(node->key, str, i);
        // ft_printf("key: %s\n", node->key);

    }
    return (node);
}


static int	add_end(t_node **stack, char *str)
{
	t_node	*pre;
	t_node	*last;

	last = malloc(sizeof(t_node));
	if (!last)
		return (1);
	last->next = NULL;
    // printf("inside add_end\n");
    last = parse_str(last, str);
	// last->line = ft_strdup(str); //////// added to function above to split the lines
    // printf("after strdup; line: %s\n", last->line);
	if (!(*stack))
	{
        // printf("inside add_end if\n");
		*stack = last;
		last->prev = NULL;
	}
	else
	{
        pre = find_last(*stack); 
        // printf("inside add_end else\n");
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

void load_list(char **envp, t_node **env)
{
    int i;

    i = 0;
    // printf("Load_list\n");
    while (envp[i])
    {
        if (add_end(env, envp[i]))
        {
            free_env(env);
            write(1, "Error\n", 6);
            exit(1);
        }
        // printf("another line\n");
        i++;
    }

}



void    command_search(t_bananas *bana, char **envp, t_node **env)
{
    int i;

    i = 0;
    // printf("command_search\n");
    if(bana->is_pipe)
        pipex(bana, envp);
    else if(bana->is_rdr)
        redirections(bana, envp);
    else
        built_ins(bana, env);
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
}
