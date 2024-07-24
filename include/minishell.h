/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:32:12 by dmusulas          #+#    #+#             */
/*   Updated: 2024/07/18 18:15:27 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


//NOTE: probably will split this header file into multiple ones for tidyness
//later

#ifndef MINISHELL_H 
# define MINISHELL_H

/* HEADERS */
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, exit, getenv
#include <unistd.h> // read, write, access, open, close, fork,
				// getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty
				// ttyname, ttyslot
#include <sys/wait.h> // wait, waitpid, wait3, wait4
#include <sys/types.h> // fork, stat, lstat, fstat, opendir, readdir, closedir
//#include <dirent.h> // opendir, readir, closedir
//#include <sys/stat.h> // stat, lstat, fstat
#include <signal.h> // signal, igaction, sigemptyset, sigaddset, kill
#include <readline/readline.h> // readline
#include <readline/history.h> // rl_clear_history, rl_on_new_line, rl_replace_line
						// rl_redisplay, add_history
#include <termios.h> // tcstattr, tcgetattr
#include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <errno.h> // sterror, perror
#include <sys/ioctl.h> // ioctl

#include "lexer_parser.h"

/* MACROS */
#define RL_MSG "minitest"

#endif
