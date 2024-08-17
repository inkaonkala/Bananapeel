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
