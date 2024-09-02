/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:17:02 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 21:15:08 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

/*
	T_REDIR_IN <
	T_REDIR_OUT >
	T_APPEND >>
	T_HEREDOC <<
*/

typedef enum s_tokens
{
	T_PIPE = 1,
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
	t_lexer			*lexer;
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
	char	**envp;
	char	**paths;
	t_lexer	*lexer_lst;
	t_lexer	*p_redir;
	int		redir_num;
	int		pipes;
	int		in_fd;
	int		out_fd;
	bool	heredoc;
	// bool	loop_reset;
	t_ast	*tree;
}	t_tools;

/* LEX_UTILS */
t_lexer	*make_tk(char *str, t_tokens token);
void	add_tk(t_lexer **lexer_list, t_lexer *new_token);
int		ft_one_tk(char c, t_tools *tools);
int		ft_two_tk(char c1, char c2, t_tools *tools);
int		check_quotes(char *s);

/* LEXER */
int		tokenize_input(t_tools *tools);

/* PARSE_PREP */
void	add_tk_cmd_check(char *str, t_tools *tools);
// void	label_cmds(t_tools *tools);
void	process_tokens(t_tools *tools);
void	handle_input(t_tools *tools);

/* PARSE_UTILS */
int		is_builtin(const char *cmd);
t_ast	*ast_new(void);
int		parse_input(t_tools *tools);

/* PARSER */
char	*parse_arg(const char *s);
t_ast	*parse_cmd(t_lexer **tokens);
t_ast	*parse_pipe(t_lexer **tokens);
t_ast	*parse_redir(t_lexer **tokens);

/* EXPAND */
#endif
