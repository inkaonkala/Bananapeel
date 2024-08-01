
#ifndef BANANA_PEEL
# define BANANA_PEEL

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> // for pipex
# include  "libft/libft.h"


// extern int global;

typedef struct s_bananas
{
    int		fd_output;
    int		fd_input;
	
    int		tok_num;

    char	**token;
    char	**cmd_paths;
    char    **cmd_args;

	int		**pipes;

    bool    is_valid_intake;

}   t_bananas;


//in built_ins.c
void	built_ins(t_bananas *bana);

//in parsing.c
bool	parsing(char *str, t_bananas *bana, char **envp);
int		empties(char c);

//in little_helpers.c
int		empties(char c);
int		quote_chk(char *str, char *cur_quo, int i);
bool	check_specials(char *token);

// in here_dog.c
void	find_dog(char *str);
void	handle_the_dog(const char *delimiter);

// in delimiter.c
char	*find_delimiter(char *str);

// in token_checker.c
void	command_search(t_bananas *bana, char **envp);

// pipes_are_calling

void	free_char_array(char ***paths, int arc);
int     pipex(t_bananas *bana, char **envp);
bool    parse_cmd_line(t_bananas *bana, char **envp);
bool	check_arguments(t_bananas *bana);
bool	parse_cmd_args(t_bananas *bana);
void	clean_n_errors(t_bananas *bana);
int     create_child(t_bananas *bana, char **envp, int index);
void	init_pipes(t_bananas *bana);
void	free_line(char **paths, int arc);


#endif
