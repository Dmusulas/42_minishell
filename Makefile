# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 17:18:14 by dmusulas          #+#    #+#              #
#    Updated: 2024/07/05 17:34:18 by dmusulas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC           	= cc
CFLAGS       	= -Wall -Wextra -Werror -g -Iinclude -Isrc
NAME         	= minishell
MAKE_LIB     	= make -C
RM			 	= rm -rf

# Libraries
LIBFT_DIR    	= libft
LIBFT_FILENAME  = libft.a
LIBFT        	= $(LIBFT_DIR)/$(LIBFT_FILENAME)
CFLAGS			+= -I$(LIBFT_DIR)/include

# Sources
VPATH        	= src:include
INCLUDES     	= minishell.h
MINISHELL_SRCS  = main.c

MINISHELL_OBJS = $(MINISHELL_SRCS:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(MINISHELL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) $(LIBFT) -o $@

$(MINISHELL_OBJS): obj/%.o : src/%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf obj

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
