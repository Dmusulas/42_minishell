#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 17:18:14 by dmusulas          #+#    #+#              #
#    Updated: 2024/09/02 16:42:02 by clinggad         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Variables
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Isrc
# RL_CFLAGS		= -I/usr/local/Cellar/readline/8.2.10/include
# LDFLAGS			= -L/usr/local/Cellar/readline/8.2.10/lib -lreadline
LDFLAGS			= -lreadline
NAME			= minishell
MAKE_LIB		= make -C
RM				= rm -rf

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
					dbg_utils.c\
					lex/lexer.c \
					lex/lex_utils.c \
					lex/parse_prep_utils.c \
					parse/expand.c \
					parse/parse_utils.c \
					parse/parser.c

MINISHELL_OBJS	= $(MINISHELL_SRCS:%.c=obj/%.o)
OBJ_DIRS		= $(sort $(dir $(MINISHELL_OBJS)))

all: $(NAME)

# readline includes and flags for mac
# $(NAME): $(MINISHELL_OBJS) $(LIBFT)
# 		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS) -o $@

# obj/%.o: src/%.c
# 		@mkdir -p $(dir $@)
# 		$(CC) $(CFLAGS) $(LIBFT_CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(OBJ_DIRS):
		@mkdir -p $@

$(NAME): $(OBJ_DIRS) $(MINISHELL_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS) -o $@

obj/%.o: src/%.c | $(OBJ_DIRS)
		$(CC) $(CFLAGS) $(LIBFT_CFLAGS) -c $< -o $@

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
