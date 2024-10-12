# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 16:00:41 by dmusulas          #+#    #+#              #
#    Updated: 2024/10/12 14:07:49 by pmolzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Isrc
NAME			= minishell
MAKE_LIB		= make -C
RM				= rm -rf

# OS-specific flags
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    RL_CFLAGS	= -I/usr/include/readline
    LDFLAGS		= -lreadline -lncurses
else ifeq ($(UNAME_S), Darwin) # macOS
    RL_CFLAGS	= -I/opt/homebrew/Cellar/readline/8.2.13/include
    LDFLAGS		= -L/opt/homebrew/Cellar/readline/8.2.13/lib -lreadline -lncurses
endif

# Libraries
LIBFT_DIR		= libft
LIBFT_FILENAME	= libft.a
LIBFT			= $(LIBFT_DIR)/$(LIBFT_FILENAME)
LIBFT_CFLAGS	= -I$(LIBFT_DIR)/include

# Sources
VPATH			= src:include
INCLUDES		= minishell.h \

MINISHELL_SRCS	= main.c \
				  signals.c \
				  mini_loop.c \
				  clean_up.c \
				  err_msg.c \
				  env/dup_env.c\
				  env/clean.c\
				  lex/lexer.c \
				  lex/lex_utils.c \
				  lex/parse_prep_utils.c \
				  parse/expand.c \
				  parse/parse_utils.c \
				  parse/parser.c\
				  builtins/builtins.c\
				  builtins/builtins_utils.c\
				  utils/debug.c\
				  utils/arrays.c\
				  exec/err.c\
				  exec/executor.c\
				  exec/io.c\
				  exec/path_finder.c\

MINISHELL_OBJS	= $(MINISHELL_SRCS:%.c=obj/%.o)
OBJ_DIRS		= $(sort $(dir $(MINISHELL_OBJS)))

all: $(NAME)

$(OBJ_DIRS):
		@mkdir -p $@

$(NAME): $(OBJ_DIRS) $(MINISHELL_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(RL_CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS) -o $@

obj/%.o: src/%.c | $(OBJ_DIRS)
		@mkdir -p obj
		$(CC) $(CFLAGS) $(LIBFT_CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(LIBFT):
		$(MAKE_LIB) $(LIBFT_DIR)

clean:
		make clean -C $(LIBFT_DIR)
		$(RM) obj

fclean: clean
		make fclean -C $(LIBFT_DIR)
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
