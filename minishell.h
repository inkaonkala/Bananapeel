
#ifndef BANANA_PEEL
# define BANANA_PEEL

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include  "libft/libft.h"


// extern int global;

typedef struct s_bananas
{
    int		fd_output;
    int		fd_input;
	int		tok_num;

    char	**token;
    char	**cmd_paths;

}   t_bananas;


//in built_ins.c
void	built_ins(char *str);

//in parsing.c
void	parsing(char *str);
int		empties(char c);

//in little_helpers.c
int	empties(char c);
int	quote_chk(char *str, char *cur_quo, int i);

// in here_dog.c
void	find_dog(char *str);
void	handle_the_dog(const char *delimiter);

// in delimiter.c
char	*find_delimiter(char *str);

// in token_checker.c
void	command_search(t_bananas *bana);

#endif
