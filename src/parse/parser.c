/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:46 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 19:40:34 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "libft.h"
#include "minishell.h"

/**
 * Parses the input from lexer tokens and constructs an AST.
 * Handles commands, pipes, and redirections in one loop.
 *
 * @param tools The tools structure containing lexer and other resources.
 * @return The root node of the constructed AST or NULL on failure.
 */
int	parse_input(t_tools *tools)
{
	t_ast	*cmd_node;
	t_ast	*parent_node;

	cmd_node = NULL;
	parent_node = NULL;
	while (tools->lexer_lst)
	{
		if (tools->lexer_lst->token == T_CMD)
		{
			cmd_node = parse_cmd(tools);
			if (!cmd_node)
				return (0);
			if (!parent_node)
				parent_node = cmd_node;
		}
		else if (tools->lexer_lst->token == T_PIPE)
		{
			parent_node = handle_pipe(parent_node, tools);
			if (!parent_node)
				return (0);
		}
		else if (is_redirection(tools->lexer_lst->token))
		{
			parent_node = handle_redir(parent_node, tools);
			if (!parent_node)
				return (0);
		}
		else if (tools->lexer_lst->token == T_ARG && cmd_node)
		{
			parse_arg(cmd_node, tools);
		}
		else
			tools->lexer_lst = tools->lexer_lst->next;
	}
	tools->tree = parent_node;
	return (1);
}
