#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

#include "minishell.h"

/*
REDIR_OUT (>)
APPEND_OUT (>>)
REDIR_IN (<)
HEREDOC_IN (<<)
*/
typedef enum s_tokens
{
	PIPE,
	REDIR_OUT,
	APPEND_OUT,
	REDIR_IN,
	HEREDOC_IN,
}	t_tokens;

/*
*str: hold command/argument
token: token type as defined by t_tokens
i: index to position token place
*next: ptr to next token
*prev:  ptr to prev token
*/
typedef struct s_lexer
{
	char			*str;
	t_tokens			token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

/*
*lexer_lst: ptr to head of lexer list containing tokens
*redir: ptr to a lexer list specifically holding redirection tokens 
redir_num: number of redir tokens found
*/
typedef struct s_parser
{
	t_lexer			*lexer_lst;
	t_lexer			*redir;
	int				redir_num;
}	t_parser;

/*
*args: str of argument for curr cmd
**paths: arr of paths where exec may be found (PATH env variable)
**envp: arr of environment varriables
*lexer_lst: ptr to head of lexer list
*pwd: curr working directory (env PATH=PWD)
*old_pwd: old working directory (env PATH=OLDPWD (only there if cd))
reset: flag if parser state needs to be reset
*/
typedef struct s_tools
{
	char			*args;
	char			**paths;
	char			**envp;
	t_lexer			*lexer_lst;
	char			*pwd;
	char			*old_pwd;
	int				reset;
}	t_tools;

#endif