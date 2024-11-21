/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:49:09 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 19:43:08 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/**
 * Parses arguments for a command node and attaches them to the right.
 *
 * @param cmd_node The command node to attach arguments to.
 * @param tools The tools structure containing lexer and other resources.
 */
void	parse_arg(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;
	t_ast	*new_arg;

	current = cmd_node;
	while (current->right)
		current = current->right;
	while (tools->lexer_lst && tools->lexer_lst->token == T_ARG)
	{
		new_arg = ast_add_child(current, true, tools);
		if (!new_arg)
			return ;
		new_arg->token = tools->lexer_lst->token;
		new_arg->str = trim_expd_arg(tools->lexer_lst->str, tools);
		if (!new_arg->str)
			return ;
		current = new_arg;
		tools->lexer_lst = tools->lexer_lst->next;
	}
}

/**
 * Parses a command or argument and creates the corresponding AST node.
 *
 * @param tools The tools structure containing lexer and other resources.
 * @return The created command node or NULL on failure.
 */
t_ast	*parse_cmd(t_tools *tools)
{
	t_ast	*cmd_node;

	cmd_node = ast_new(tools);
	if (!cmd_node)
		return (NULL);
	cmd_node->token = tools->lexer_lst->token;
	cmd_node->str = ft_strdup(tools->lexer_lst->str);
	if (!cmd_node->str)
		return (free_ast(cmd_node), NULL);
	if (is_builtin(cmd_node->str))
		cmd_node->b_cmd = true;
	tools->lexer_lst = tools->lexer_lst->next;
	if (tools->lexer_lst && tools->lexer_lst->token == T_ARG)
		parse_arg(cmd_node, tools);
	return (cmd_node);
}
