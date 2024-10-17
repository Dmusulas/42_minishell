/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:01:54 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

bool	token_check(t_tokens tk)
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

t_ast	*ast_new(void)
{
	t_ast	*new_nd;

	new_nd = malloc(sizeof(t_ast));
	if (!new_nd)
	{
		perror("ast_new: malloc");
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
