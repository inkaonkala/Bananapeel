# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/09/23 09:39:35 by iniska           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	bananapeel

FLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

SRCFILES 	= 	bananapeel.c \
				sig/signaling.c \
				sig/terminal_configuration.c \
				broom/little_helpers.c \
				broom/clean_n_exit.c \
				broom/broom_n_vacuum.c \
				broom/freeing.c \
				builders/cdeeznuts.c \
				builders/coyotes.c \
				builders/export.c \
				builders/handle_exit.c \
				builders/dollar_store.c \
				builders/built_ins.c \
				builders/built_ins_helpers.c \
				builders/no_path.c \
				token/linked_lists.c \
				token/token_checker.c \
				token/token_stuff.c \
	 			token/parsing.c \
				token/banananice.c \
				token/env_node.c \
	 			dog/here_dog.c \
	 			dog/delimiter.c \
				dog/dog_signals.c \
				dog/handle_dog.c \
				dog/here_dog_utils.c \
				rdr/funky_arrows.c \
				rdr/file_handling.c \
				rdr/file_malloc.c \
				rdr/open_files.c \


PIPEFILES	=	eleven_pipers_piping.c \
				arguments.c\
				command_line.c \
				exec_command.c \
				files.c \
				init_pipes.c \
				in_n_out_put.c \
				get_path.c \
				pipe_helpers.c \
				forks.c \
				create_child.c \
				rdr_checker.c \
				
SRCDIR		=	srcs
PIPEDIR		=	pipes_are_calling
OBJDIR		=	objs

HEADER		=	minishell.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	$(addprefix $(SRCDIR)/, $(SRCFILES)) \
				$(addprefix $(PIPEDIR)/, $(PIPEFILES))

OBJS		= 	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS)) \
				$(patsubst $(PIPEDIR)/%.c, $(PIPEDIR)/%.o, $(PSRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER) 
				@mkdir -p $(dir $@)
				@cc $(FLAGS) -o $@ -c $<

$(OBJDIR)/%.o:	$(PIPEDIR)/%.c $(HEADER)
				@mkdir -p $(dir $@)
				@cc $(FLAGS) -o $@ -c $<

$(NAME):		$(OBJS) $(LIBFT)
				@cc $(HEADERS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
				@echo "$(ANSI_CYAN)Compilation Complete: $(NAME) $(ANSI_RESET)"

$(LIBFT):		
				@make -C $(LIBFT_DIR)
				@echo "$(ANSI_CYAN)LIBFT Compiled! $(ANSI_RESET)"

clean:
				@rm -rf $(OBJDIR)
				@rm -f $(PIPEDIR)/*.o   #this is useless i Think#
				@make -C $(LIBFT_DIR) clean
				@echo "$(ANSI_RED)Objects and LIB_FT Cleaned$(ANSI_RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@make -C $(LIBFT_DIR) fclean
				@echo "$(ANSI_RED)Executable $(NAME) removed$(ANSI_RESET)"

re:				fclean all
