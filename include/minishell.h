/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:18:12 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/22 18:11:53 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

/* HEADERS */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <term.h>
# include <errno.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "lexer_parser.h"

# define ERR_LEX 1
# define ERR_QUO 2

/* MINI LOOP */
void	init_tools(t_tools *tools);
int		reset_tools(t_tools *tools);
int		mini_loop(t_tools *tools);
void	clean_tools(t_tools *tools);

int		ft_error(int err_type, t_tools *tools);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);

void	print_tokens(t_lexer *lexer_list);
void	clear_tokens(t_lexer **lexer_list);

#endif
