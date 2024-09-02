# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 15:54:31 by jbremser          #+#    #+#              #
#    Updated: 2024/09/02 16:11:38 by etaattol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= 	bananapeel

FLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

SRCFILES 	= 	bananapeel.c \
				signaling.c \
				little_helpers.c \
	 			built_ins.c \
				built_ins_helpers.c \
	 			parsing.c \
	 			here_dog.c \
	 			delimiter.c \
				token_checker.c \
				funky_arrows.c \
				file_handling.c \
				linked_lists.c \
				clean_n_exit.c \
				here_dog_utils.c \
				cdeeznuts.c \
				coyotes.c \
				terminal_configuration.c

PIPEFILES	=	eleven_pipers_piping.c \
				arguments.c\
				clean_n_errors.c \
				command_line.c \
				exec_command.c \
				files.c\
				init_pipes.c\
				in_n_out_put.c
				
SRCDIR		=	srcs
PIPEDIR		=	pipes_are_calling
OBJDIR		=	objs

HEADER		=	minishell.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	$(addprefix $(SRCDIR)/, $(SRCFILES)) \

PSRCS		=	$(addprefix $(PIPEDIR)/, $(PIPEFILES))

OBJS		= 	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS)) \
				$(patsubst $(PIPEDIR)/%.c, $(PIPEDIR)/%.o, $(PSRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER) 
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(OBJDIR)/%.o:	$(PIPEDIR)/%.c $(HEADER)
				@mkdir -p $(OBJDIR)
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
