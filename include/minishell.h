/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:32:12 by dmusulas          #+#    #+#             */
/*   Updated: 2024/07/31 15:44:36 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


//NOTE: probably will split this header file into multiple ones for tidyness
//later

#ifndef MINISHELL_H 
# define MINISHELL_H

/* HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <term.h>
#include <errno.h>
#include <sys/ioctl.h>

// #include "lexer_parser.h"

/*
implement variables as we continue so we don't have unused vars when running make
*/
typedef struct s_tools
{
	char			*args;
}	t_tools;

/* MINI LOOP */
int		reset_loop(t_tools *tools);
int		mini_loop(t_tools *tools);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);

#endif
