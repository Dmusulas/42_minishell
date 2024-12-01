/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:31:16 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

bool	is_redirection(t_tokens tk)
{
	return (tk == T_REDIR_IN || tk == T_REDIR_OUT || tk == T_APPEND
		|| tk == T_HEREDOC);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

t_ast	*ast_new(t_tools *tools)
{
	t_ast	*new_nd;

	new_nd = malloc(sizeof(t_ast));
	if (!new_nd)
	{
		ft_error(ERR_MALLOC_FAIL, tools);
		return (NULL);
	}
	new_nd->str = NULL;
	new_nd->token = 0;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->file = NULL;
	new_nd->b_cmd = false;
	return (new_nd);
}

t_ast	*ast_add_child(t_ast *parent, bool is_right, t_tools *tools)
{
	t_ast	*new_nd;

	new_nd = ast_new(tools);
	if (!new_nd)
		return (NULL);
	if (parent == NULL)
		return (new_nd);
	if (is_right)
		parent->right = new_nd;
	else
		parent->left = new_nd;
	return (new_nd);
}

char	*trim_expd_arg(const char *s, t_tools *tools)
{
	if (!s)
		return (NULL);
	if ((s[0] == '\'' || s[0] == '"') && s[0] == s[ft_strlen(s) - 1])
		return (handle_quoted_string(s, tools));
	return (process_unquoted_string(s, tools));
}
