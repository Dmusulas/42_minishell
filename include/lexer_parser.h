/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:17:02 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/22 17:29:37 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
*redir: list of redir tokens
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
	t_lexer	*redir;
	int		redir_num;
	int		pipes;
	int		in_fd;
	int		out_fd;
	//heredoc flag

}	t_tools;

t_lexer	*make_tk(char *str, t_tokens token);
void	add_tk(t_lexer **lexer_list, t_lexer *new_token);
int		ft_one_tk(char c, t_tools *tools);
int		ft_two_tk(char c1, char c2, t_tools *tools);
int		tokenize_input(t_tools *tools);
int		check_quotes(char *s);

#endif
