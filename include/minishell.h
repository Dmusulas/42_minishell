/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:18:12 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 19:33:01 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NOTE: probably will split this header file into multiple ones for tidyness
//later

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
# include "exec.h"
# include "libft.h"

// #include "lexer_parser.h"

/*
implement variables as we continue so we don't have unused vars when running make
*/
typedef struct s_tools
{
	char			*args;
	char			**envp;
	char			**argv;
	t_bool			debug_mode;
}	t_tools;

/* MINI LOOP */
void	reset_tools(t_tools *tools);
void	mini_loop(t_tools *tools);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);

#endif
