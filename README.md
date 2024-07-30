# Bananapeel
A little shell to be born ...

A simple route to follow:

Directory Structure
minishell/
│
├── src/
│   ├── main.c
│   ├── prompt.c
│   ├── parser.c
│   ├── execution.c
│   ├── builtins.c
│   ├── redirection.c
│   ├── pipe.c
│   └── utils.c
│
├── include/
│   └── minishell.h
│
└── Makefile

Function Tree
main.c

main():
{
  Initialize the shell.
  Enter the main loop to handle user input.
  Handle signals (e.g., SIGINT, SIGQUIT).
  Exit and clean up.
}

prompt.c
{
  display_prompt():
    Print the shell prompt.
 read_input():
    Read user input using readline().
  parser.c
    parse_input(char *input):
      Tokenize the input based on spaces and special characters.
    handle_quotes(char *input):
      Process quoted strings to handle quoted sequences.
    handle_env_vars(char *input):
      Expand environment variables like $PATH.

execution.c
{
  execute_command(char **args):
      Fork a child process.
      Execute the command using execve().
      Handle built-in commands.
      handle_builtin_commands(char **args):
      Implement built-in commands like cd, echo, etc.
  wait_for_child_process():
      Wait for the child process to finish.
}

builtins.c
{
  builtin_echo(char **args):
      Implement the echo command.
  builtin_cd(char **args):
      Implement the cd command.
builtin_pwd():
    Implement the pwd command.
builtin_export(char **args):
    Implement the export command.
builtin_unset(char **args):
    Implement the unset command.
builtin_env():
    Implement the env command.
builtin_exit():
    Implement the exit command.
}

redirection.c
{
  handle_redirection(char **args):
    Manage input and output redirections.
  process_redirections(char **args):
    Set up file descriptors based on redirection operators (<, >, >>, <<).
}

pipe.c
{
    setup_pipes(char **args):
      Handle pipes and set up communication between processes.
  execute_pipeline(char ***cmds):
      Execute a series of commands connected by pipes.
}
utils.c
{
  free_resources():
    Clean up allocated memory.
  handle_signals():
    Set up signal handling for SIGINT, SIGQUIT, etc.
  expand_variables(char *input):
    Replace environment variables with their values.
}
