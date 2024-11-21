/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:48:19 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 19:13:58 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/**
 * Creates and links a pipe AST node, updating the previous command.
 *
 * @param prev_node The previous command node (left side of the pipe).
 * @param tools The tools structure containing lexer and other resources.
 * @return The pipe node or NULL on failure.
 */
t_ast	*handle_pipe(t_ast *prev_node, t_tools *tools)
{
	t_ast	*pipe_node;
	t_ast	*right_cmd;

	pipe_node = ast_new(tools);
	if (!pipe_node)
		return (NULL);
	pipe_node->token = T_PIPE;
	pipe_node->left = prev_node;
	tools->lexer_lst = tools->lexer_lst->next;
	right_cmd = parse_cmd(tools);
	if (!right_cmd)
		return (free_ast(pipe_node), NULL);
	while (tools->lexer_lst && is_redirection(tools->lexer_lst->token))
	{
		right_cmd = handle_redir(right_cmd, tools);
		if (!right_cmd)
			return (free_ast(pipe_node), NULL);
	}
	
	pipe_node->right = right_cmd;
	pipe_node->str = ft_strdup("|");
	return (pipe_node);
}
