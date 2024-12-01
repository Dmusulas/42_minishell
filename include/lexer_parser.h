/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:31:52 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <dirent.h>
# include "libft.h"

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
**envp: arr of environment variables
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
	char	**envp_org;
	t_list	*envp;
	t_lexer	*lexer_lst;
	t_lexer	*p_redir;
	int		in_fd;
	int		out_fd;
	int		last_pid;
	bool	heredoc;
	bool	in_single_quotes;
	t_ast	*tree;
	int		last_exit_status;
}	t_tools;

/* LEX_UTILS */
t_lexer	*make_tk(char *str, t_tokens token);
void	add_tk(t_lexer **lexer_list, t_lexer *new_token);
int		ft_one_tk(char c, t_tools *tools);
int		ft_two_tk(char c1, char c2, t_tools *tools);
int		check_quotes(char *s, t_tools *tools);
size_t	ft_strcspn(const char *s, const char *reject);

/* LEX_UTILS_3 */
int		check_tk(char tk);
void	handle_final_token(t_tools *tools, int start, int i, bool is_cmd);
int		check_quote_status(char *args, int *i, char *quote_type);

/* LEX_UTILS_4 */
void	handle_space_token(t_tools *tools, int *i, int *start, bool *is_cmd);
void	handle_special_token(t_tools *tools, int *i, int *start, bool *is_cmd);
int		handle_token_processing_core(t_tools *tools, int *i,
			char *quote_type, bool *is_cmd);
int		handle_token_processing(t_tools *tools, bool *is_cmd);

/* LEXER */
int		tokenize_input(t_tools *tools);

/* PARSE_PREP */
void	process_tokens(t_tools *tools);
void	handle_input(t_tools *tools);

/* PARSE_UTILS */
bool	is_redirection(t_tokens tk);
int		is_builtin(const char *cmd);
t_ast	*ast_new(t_tools *tools);
t_ast	*ast_add_child(t_ast *parent, bool is_right, t_tools *tools);
int		parse_input(t_tools *tools);
char	*trim_expd_arg(const char *s, t_tools *tools);
char	*handle_quoted_string(const char *s, t_tools *tools);
char	*remove_quotes(const char *temp);
char	*process_unquoted_string(const char *s, t_tools *tools);

/* PARSER */
t_ast	*parse_cmd(t_tools *tools);
void	parse_arg(t_ast *cmd_node, t_tools *tools);
t_ast	*handle_pipe(t_ast *prev_node, t_tools *tools);
t_ast	*handle_redir(t_ast *prev_node, t_tools *tools);
char	*get_env_value(const char *var_name, t_tools *tools);

/* EXPAND */
char	*expand_var(const char *s, t_tools *tools);

#endif
