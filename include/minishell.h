/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:18:12 by dmusulas          #+#    #+#             */
/*   Updated: 2024/09/02 17:43:49 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
# include <stdbool.h>
// # include "exec.h"
# include "libft.h"
# include "lexer_parser.h"

#define ERR_LEX 1
#define ERR_QUO 2
#define ERR_PAR 3

/* MINI LOOP */
void	init_tools(t_tools *tools);
int		reset_tools(t_tools *tools);
int		mini_loop(t_tools *tools);
void	clean_tools(t_tools *tools);

int		ft_error(int err_type, t_tools *tools);
void	clear_tokens(t_lexer **lexer_list);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);


/* TO BE REMOVED */
void	print_tokens(t_lexer *lexer_list);
void	print_ast_node(t_ast *node);
void	print_ast(t_ast *tree, int depth);

#endif
