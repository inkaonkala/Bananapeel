/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:12:07 by etaattol          #+#    #+#             */
/*   Updated: 2024/09/13 17:02:48 by jbremser         ###   ########.fr       */
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
# include <termios.h> // 
# include  "libft/libft.h"

# define IN_HEREDOG 1
# define OUT_HEREDOG 0

#define SET 0
#define GET 1

// extern int global;

typedef struct s_node
{
    char            *value;
    char            *key;
    struct  s_node  *next;
    struct  s_node  *prev;
}   t_node;

typedef struct s_bananas
{
    char	**token;
    int		tok_num;

    // check for token values
    bool    is_pipe;
    bool    is_rdr;
    bool    is_dog;

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
    
    // for heredog:
    int     original_stdin;
    int     heredog_interrupted;
    int     last_exit_status;

    char    **envp;
    t_node  *env;

    
}   t_bananas;



/* ************************************************************************** */
/*									built-ins								  */
/* ************************************************************************** */
void	built_ins(t_bananas *bana);
void    handle_deeznuts(t_bananas *bana, t_node *env);

/* ************************************************************************** */
/*									export           						  */
/* ************************************************************************** */
void	handle_export(t_bananas *bana);
int     add_end(t_node **stack, char *str);

/* ************************************************************************** */
/*									handle_exit        						  */
/* ************************************************************************** */
void    handle_exit(t_bananas *bana);

/* ************************************************************************** */
/*									built-ins_helpers						  */
/* ************************************************************************** */
void	handle_echo(t_bananas *bana);
int	    handle_pwd(t_bananas *bana);
void    handle_unset(t_bananas *bana, t_node **env);
void	remove_node(t_node *node);

/* ************************************************************************** */
/*									signaling								  */
/* ************************************************************************** */
void    signaling(void);
int     big_stopping(int get, int newvalue);
/* ************************************************************************** */
/*									parsing 								  */
/* ************************************************************************** */
bool	parsing(char *str, t_bananas *bana);
int		empties(char c);
/* ************************************************************************** */
/*									little_helpers							  */
/* ************************************************************************** */

int     empties(char c);
int		quote_chk(char *str, char *cur_quo, int i);
bool	check_specials(char *token);
int     number_checker(char *argv);

/* ************************************************************************** */
/*									here_dog								  */
/* ************************************************************************** */
void	find_dog(t_bananas *bana, int tk_i);
void 	handle_the_dog(const char *delimiter, t_bananas *bana);
char    get_heredog_status(void);
void    set_heredog_status(char status);
char	*readline_wrapper(const char *prompt, t_bananas *bana);

/* ************************************************************************** */
/*									delimiter								  */
/* ************************************************************************** */
char	*find_delimiter(t_bananas *bana);
/* ************************************************************************** */
/*									token_checker							  */
/* ************************************************************************** */

void    command_search(t_bananas *bana, char **envp, t_node **env);
void    token_merge(t_bananas *bana);

/* ************************************************************************** */
/*									coyotes.c								  */
/* ************************************************************************** */

void	del_quotes(t_bananas *bana);

/* ************************************************************************** */
/*							        clean_n_exit							  */
/* ************************************************************************** */

void    token_cleaner(t_bananas *bana, int i);
void    exiting(t_bananas *bana, int i);
void	free_stuff(char **args, char *path);

/* ************************************************************************** */
/*									funky_arrows							  */
/* ************************************************************************** */
void    redirections(t_bananas *bana, char **envp);
/* ************************************************************************** */
/*									file_handling							  */
/* ************************************************************************** */

void 	file_handling(t_bananas *bana);

/* ************************************************************************** */
/*									open_files  							  */
/* ************************************************************************** */

void	open_infile(t_bananas *bana, int i);
void	open_outfile(t_bananas *bana, int i, bool append);

/* ************************************************************************** */
/*									file_malloc 							  */
/* ************************************************************************** */

void	file_malloc(t_bananas *bana);

/* ************************************************************************** */
/*									linked_lists    						  */
/* ************************************************************************** */
t_node  *find_last(t_node	*stack);
t_node  *parse_str(t_node *node, char *str);
void	free_env(t_node	**env);
int     stack_len(t_node *stack);
void	load_list(t_bananas *bana, char **envp);

/* ************************************************************************** */
/*									broom_n_vacuum    						  */
/* ************************************************************************** */
void    clean_banana(t_bananas *bana);
void	clean_struct(t_bananas *bana);
char    *free_char_array(char **array);
void	free_array(char ***paths, int arc);


/* ************************************************************************** */
/*									pipes_are_calling						  */
/* ************************************************************************** */

//  arguments.c

bool	parse_cmd_args(t_bananas *bana);

// clean_n_errors.c

void	free_line(char **paths, int arc);
void	clean_n_errors(t_bananas *bana);

// command_line.c

bool    parse_cmd_line(t_bananas *bana, char **envp);

// eleven_pipers_piping.c

void	pipex(t_bananas *bana, char **envp, t_node **env);

// execute_command.c

void	execute_command(t_bananas *bana, char **envp, int index);

// create_child.c 

int		create_child(t_bananas *bana, char **envp, int index);

// files.c

bool	check_arguments(t_bananas *bana);

// forks.c

bool	fork_it(t_bananas *bana, int fd[2], pid_t *pid, int index);


// get_path.c

char	*get_path(char *path_name, char **envp);

//in_n_out_put.c

void	redirect_putput(t_bananas *bana, int fd[2], int index);
void	redirect_input(t_bananas *bana, int index);
bool	redirect_file_input(t_bananas *bana);
bool	redirect_file_putput(t_bananas *bana);

// init_pipes.c

void	init_pipes(t_bananas *bana);

// pipe_helpers.c

void	empty_prompt(void);
void	shut_fd(int fd[2]);
void	free_argh(char **argh);
void    handle_sigint_s(int sig);


// terminal_configuration.c
void	setup_terminal(struct termios *original_termios);
void	restore_terminal(const struct termios *original_termios);
char	*dollar_check(char *str, t_node *env, t_bananas *bana);

#endif
