/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:54:44 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/20 14:01:37 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANANA_PEEL
# define BANANA_PEEL

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> // for pipex
# include  "libft/libft.h"


// extern int global;

typedef struct s_bananas
{
    char	**token;
    int		tok_num;

    // check for token values
    bool    is_pipe;
    bool    is_rdr;
    //bool    is_dog;

    // for file_handling
    int     *in_files;
    int     *out_files;
    int     infile_count;
    int     outfile_count;

    //for pipex:
    char	**cmd_paths;
    char    **cmd_args;

	int		**pipes;
    int     prev_fd[2];
    int		fd_output;
    int		fd_input;

    bool    is_valid_intake;
    bool    has_input;

}   t_bananas;

typedef struct s_node
{
    char            *value;
    char            *key;
    struct  s_node  *next;
    struct  s_node  *prev;
}   t_node;


/* ************************************************************************** */
/*									built-ins								  */
/* ************************************************************************** */
void	built_ins(t_bananas *bana, t_node **env);
/* ************************************************************************** */
/*									signaling								  */
/* ************************************************************************** */
void    signaling(void);
/* ************************************************************************** */
/*									parsing 								  */
/* ************************************************************************** */
bool	parsing(char *str, t_bananas *bana, t_node **env);
int		empties(char c);
/* ************************************************************************** */
/*									little_helpers							  */
/* ************************************************************************** */
void    token_cleaner(t_bananas *bana, int i);
int     empties(char c);
int		quote_chk(char *str, char *cur_quo, int i);
bool	check_specials(char *token);
int     number_checker(char *argv);
/* ************************************************************************** */
/*									here_dog								  */
/* ************************************************************************** */
void	find_dog(t_bananas *bana);
void	handle_the_dog(const char *delimiter);
/* ************************************************************************** */
/*									delimiter								  */
/* ************************************************************************** */
char	*find_delimiter(t_bananas *bana);
/* ************************************************************************** */
/*									token_checker							  */
/* ************************************************************************** */
void    command_search(t_bananas *bana, char **envp, t_node **env);

/* ************************************************************************** */
/*									funky_arrows							  */
/* ************************************************************************** */
void    redirections(t_bananas *bana, char **envp);
/* ************************************************************************** */
/*									file_handling							  */
/* ************************************************************************** */
bool  file_handling(t_bananas *bana, int i);
void    file_malloc(t_bananas *bana);
/* ************************************************************************** */
/*									linked_lists    						  */
/* ************************************************************************** */
t_node  *find_last(t_node	*stack);
t_node  *parse_str(t_node *node, char *str);
int     add_end(t_node **stack, char *str);
void	free_env(t_node	**env);
int     stack_len(t_node *stack);
void    load_list(char **envp, t_node **env);


/* ************************************************************************** */
/*									pipes_are_calling						  */
/* ************************************************************************** */

void	free_char_array(char ***paths, int arc);
int     pipex(t_bananas *bana, char **envp);

char	*get_path(char *path_name, char **envp);
bool    parse_cmd_line(t_bananas *bana, char **envp);


bool	parse_cmd_args(t_bananas *bana);
void	clean_n_errors(t_bananas *bana);
int     create_child(t_bananas *bana, char **envp, int index);
void	init_pipes(t_bananas *bana);
void	free_line(char **paths, int arc);

// files.c
bool	check_arguments(t_bananas *bana);
bool	redirect_file_input(t_bananas *bana);
void	redirect_file_putput(t_bananas *bana);


#endif
