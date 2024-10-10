/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/10 16:37:38 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

/*
	T_REDIR_IN <
	T_REDIR_OUT >
	T_APPEND >>
	T_HEREDOC <<
*/
typedef enum s_tokens
{
	T_INVALID = 0,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_ARG,
	T_CMD,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_ast
{
	char			*str;
	t_tokens		token;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*file;
	bool			b_cmd;
}	t_ast;

/*
*args: str of argument for curr cmd
**paths: arr of paths where exec may be found (PATH env variable)
**envp: arr of environment varriables
*lexer_lst: ptr to head of lexer list
*p_redir: ptr to curr redir token in lexer_lst

pipes" pipe count

*pwd: curr working directory (env PATH=PWD)
*old_pwd: old working directory (env PATH=OLDPWD (only there if cd))
reset: flag if parser state needs to be reset (fork cases)

implement variables as we continue so we don't have unused vars when running make
*/
typedef struct s_tools
{
	char	*args;
	t_lexer	*lexer_lst;
	t_lexer	*p_redir;
	int		redir_num;
	int		pipes;
	int		in_fd;
	int		out_fd;
	bool	heredoc;
	bool	debug_mode;
	t_ast	*tree;
}	t_tools;

/* LEX_UTILS */
t_lexer	*make_tk(char *str, t_tokens token);
void	add_tk(t_lexer **lexer_list, t_lexer *new_token);
int		ft_one_tk(char c, t_tools *tools);
int		ft_two_tk(char c1, char c2, t_tools *tools);
int		check_quotes(char *s);
size_t	ft_strcspn(const char *s, const char *reject);

/* LEXER */
int		handle_q_arg(char *s, int start, t_tools *tools);
int		handle_arg(char *s, int start, t_tools *tools);
int		tokenize_input(t_tools *tools);

/* PARSE_PREP */
// void	add_tk_cmd_check(char *str, t_tools *tools);
// void	label_cmds(t_tools *tools);
void	process_tokens(t_tools *tools);
void	handle_input(t_tools *tools);

/* PARSE_UTILS */
bool	token_check(t_tokens tk);
int		is_builtin(const char *cmd);
t_ast	*ast_new(void);
int		parse_input(t_tools *tools);
void	execute_ast(t_tools *tools);

/* PARSER */
// char	*trim_expd_arg(const char *s);
t_ast	*parse_cmd(t_tools *tools);
t_ast	*parse_pipe(t_tools *tools);
t_ast	*parse_redir(t_tools *tools);

/* EXPAND */
char	*expand_var(const char *s, t_tools *tools);

#endif
