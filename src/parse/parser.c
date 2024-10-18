/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:46 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/08 21:55:16 by pmolzer          ###   ########.fr       */
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
	t_ast	*prev_node;
	t_lexer	*curr_lexer;

	cmd_node = NULL;
	prev_node = NULL;
	curr_lexer = tools->lexer_lst;
	while (curr_lexer)
	{
		if (curr_lexer->token == T_CMD || curr_lexer->token == T_ARG)
		{
			cmd_node = parse_cmd(tools);
			if (!cmd_node)
				return (0);
			if (!prev_node)
				prev_node = cmd_node;
		}
		else if (curr_lexer->token == T_PIPE)
		{
			prev_node = handle_pipe(prev_node, tools);
			if (!prev_node)
				return (0);
		}
		else if (token_check(curr_lexer->token))
		{
			prev_node = handle_redir(prev_node, tools);
			if (!prev_node)
				return (0);
		}
		curr_lexer = tools->lexer_lst;
	}
	tools->tree = prev_node;
	tools->tree = swap_redirection_nodes(tools->tree);
	return (1);
}
