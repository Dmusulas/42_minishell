#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clinggad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 17:18:14 by dmusulas          #+#    #+#              #
#    Updated: 2024/07/31 15:29:18 by clinggad         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Variables
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Isrc
# RL_CFLAGS		= -I/usr/local/Cellar/readline/8.2.10/include
# LDFLAGS			= -L/usr/local/Cellar/readline/8.2.10/lib -lreadline
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

MINISHELL_OBJS  = $(MINISHELL_SRCS:%.c=obj/%.o)

all: $(NAME)

# readline includes and flags for mac
# $(NAME): $(MINISHELL_OBJS) $(LIBFT)
# 		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) $(LDFLAGS) -o $@

# obj/%.o: src/%.c
# 		@mkdir -p obj
# 		$(CC) $(CFLAGS) $(LIBFT_CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(NAME): $(MINISHELL_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) -o $@

obj/%.o: src/%.c
		@mkdir -p obj
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
