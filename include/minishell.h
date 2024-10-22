/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:38:38 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 14:31:26 by pmolzer          ###   ########.fr       */
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
# include <stdbool.h>
// # include "exec.h"
# include "libft.h"
# include "lexer_parser.h"
# include "error_messages.h"

# define ERR_LEX 1
# define ERR_QUO 2
# define ERR_PAR 3

/* MINI LOOP */
void	set_initial_exit_status(t_tools *tools);
void	init_tools(t_tools *tools);
int		reset_tools(t_tools *tools);
int		mini_loop(t_tools *tools);
void	clean_tools(t_tools *tools);

void	clear_tokens(t_lexer **lexer_list);
void	free_ast(t_ast *tree);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);

/* TO BE REMOVED */

/* ENVP */
void	delete_duplicated_envp(t_tools *tools);
int		duplicate_env(t_tools *tools);
int		update_or_add_envp(t_list **lst, const char *new_envp);
int		cmp_envp(void *a, void *b);

/* MINI LOOP */
int		mini_loop(t_tools *tools);

/* SIGNALS */
int		event(void);
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	init_signals(void);

/* UTILS */
void	free_2darray(char **array);
char	**list_to_array(t_list *list);
/* DEBUG */

void	print_tokens(t_lexer *lexer_list);
void	print_ast_node(t_ast *node);
void	print_ast(t_ast *tree, int depth);
void	print_linkedlist(t_list *lst);
void	test_envp(t_list *envp);

/* BUILTINS */
void	execute_builtin(t_ast *cmd_node, t_tools *tools);
void	remove_env_var(t_list **envp, const char *var_name);
int		change_to_absolute_path(char *path, t_tools *tools);
int		change_to_relative_path(char *path, t_tools *tools);
int		ft_export(t_ast *cmd_node, t_tools *tools);
int		ft_echo(t_ast *cmd_node, t_tools *tools);
int		ft_unset(t_ast *cmd_node, t_tools *tools);
int		ft_cd(char *path, t_tools *tools);
void	ft_exit(t_tools *tools);
int		ft_env(t_tools *tools);

#endif
