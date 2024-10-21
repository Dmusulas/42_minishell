/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:47:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 15:17:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static t_ast	*make_redir(t_ast *cmd_node, t_lexer *token, char *file_str, t_tools tools)
{
	t_ast	*redir_node;

	redir_node = ast_new(&tools);
	if (!redir_node)
		return (free_ast(cmd_node), NULL);
	redir_node->token = token->token;
	redir_node->left = cmd_node;
	redir_node->file = ft_strdup(file_str);
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

	redir_node = make_redir(prev_node, tools->lexer_lst,
			tools->lexer_lst->next->str, *tools);
	if (!redir_node)
		return (NULL);
	tools->lexer_lst = tools->lexer_lst->next->next;
	return (redir_node);
}

/**
 * Swaps redirection nodes if an output redirection (>, >>) is
 * incorrectly placed before an input redirection (<<, <) in the AST.
 *
 * @param node The root of the AST or subtree to rearrange.
 * @return The new root node after rearranging.
 */
t_ast	*swap_redirection_nodes(t_ast *node)
{
	t_ast	*temp;

	if (!node)
		return (NULL);
	node->left = swap_redirection_nodes(node->left);
	node->right = swap_redirection_nodes(node->right);
	if ((node->token == T_REDIR_OUT || node->token == T_APPEND) && (node->left
			&& (node->left->token == T_REDIR_IN
				|| node->left->token == T_HEREDOC)))
	{
		temp = node->left;
		node->left = temp->left;
		temp->left = node;
		return (temp);
	}
	return (node);
}
