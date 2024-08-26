/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:17:02 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/26 18:06:06 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	T_CMD
}	t_tokens;

// typedef enum s_builtin
// {
// 	T_ECHO = 1,
// 	T_EXIT,
// 	T_PWD,
// 	T_CD,
// 	T_UNSET,
// 	T_ENV,
// 	T_EXP
// }	t_builtin;

typedef struct s_lexer
{
	char			*str;
	t_tokens			token;
	struct s_lexer	*next;
}	t_lexer;




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
}	t_tools;

t_lexer	*make_tk(char *str, t_tokens token);
void	add_tk(t_lexer **lexer_list, t_lexer *new_token);
int		ft_one_tk(char c, t_tools *tools);
int		ft_two_tk(char c1, char c2, t_tools *tools);
int		check_quotes(char *s);

int		tokenize_input(t_tools *tools);

void	add_tk_cmd_check(char *str, t_tools *tools);
void	label_cmds(t_tools *tools);
void	process_tokens(t_tools *tools);
void	handle_input(t_tools *tools);


#endif
