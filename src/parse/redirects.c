/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:47:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 20:23:32 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "lexer_parser.h"
#include "minishell.h"

/**
 * Creates a redirection node and links it to the command node.
 *
 * @param cmd_node The command node to which the redirection applies.
 * @param token The current lexer token representing the redirection operator.
 * @param file_str The string representing the file for redirection.
 * @return The redirection node or NULL on failure.
 */
static t_ast	*make_redir(t_ast *cmd_node, t_lexer *token, char *file_str,
		t_tools *tools)
{
	t_ast	*redir_node;

	redir_node = ast_add_child(cmd_node, false, tools);
	if (!redir_node)
		return (free_ast(cmd_node), NULL);
	redir_node->token = token->token;
	redir_node->file = trim_expd_arg(file_str, tools);
	if (!redir_node->file)
		return (free_ast(redir_node), NULL);
	return (redir_node);
}

/**
 * Creates and links a redirection AST node, updating the command.
 *
 * @param prev_node The previous command node to apply redirection to.
 * @param tools The tools structure containing lexer and other resources.
 * @return The redirection node or NULL on failure.
 */
t_ast	*handle_redir(t_ast *prev_node, t_tools *tools)
{
	t_ast	*redir_node;
	t_ast	*last_redir;

	last_redir = NULL;
	while (tools->lexer_lst && is_redirection(tools->lexer_lst->token))
	{
		if (last_redir)
		{
			redir_node = make_redir(last_redir, tools->lexer_lst,
					tools->lexer_lst->next->str, tools);
		}
		else
		{
			redir_node = make_redir(prev_node, tools->lexer_lst,
					tools->lexer_lst->next->str, tools);
		}
		if (!redir_node)
			return (NULL);
		last_redir = redir_node;
		tools->lexer_lst = tools->lexer_lst->next->next;
	}
	return (prev_node);
}
