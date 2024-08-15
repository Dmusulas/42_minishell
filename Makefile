# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 17:22:18 by dmusulas          #+#    #+#              #
#    Updated: 2024/08/15 19:43:04 by dmusulas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Isrc
RL_CFLAGS		= -I/opt/homebrew/opt/readline/include
LDFLAGS			= -L/opt/homebrew/opt/readline/lib -lreadline
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
					exec/err.c \
					exec/executor.c \
					exec/io.c \
					exec/parser.c \
					exec/utils.c

MINISHELL_OBJS  = $(MINISHELL_SRCS:%.c=obj/%.o)

all: $(NAME)

# readline includes and flags for mac
$(NAME): $(MINISHELL_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS) -o $@

obj/%.o: src/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(LIBFT_CFLAGS) $(RL_CFLAGS) -c $< -o $@

# $(NAME): $(MINISHELL_OBJS) $(LIBFT)
# 		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) -o $@


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
