#include "../minishell.h"

void    command_search(t_bananas *bana, char **envp)
{
    //if(bana->token[0] != executable)
    //    free_tokens(bana);

    //else if(bana->is_dog && !bana->is_pipe)
    //    here_dog(bana);

    if(bana->is_pipe)
        pipex(bana, envp);
    else if(bana->is_rdr)
        redirections(bana);
    else
        built_ins(bana, envp);
}
