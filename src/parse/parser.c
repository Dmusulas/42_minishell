/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:46 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:28:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "libft.h"
#include "minishell.h"

static t_ast	*handle_command_token(t_ast *parent_node, t_ast *cmd_node,
					t_tools *tools)
{
	cmd_node = parse_cmd(tools);
	if (!cmd_node)
		return (NULL);
	if (!parent_node)
		parent_node = cmd_node;
	return (parent_node);
}

static t_ast	*process_token(t_ast *parent_node, t_ast *cmd_node,
					t_tools *tools)
{
	if (tools->lexer_lst->token == T_CMD)
	{
		parent_node = handle_command_token(parent_node, cmd_node, tools);
		if (!parent_node)
			return (NULL);
	}
	else if (tools->lexer_lst->token == T_PIPE)
	{
		parent_node = handle_pipe(parent_node, tools);
		if (!parent_node)
			return (NULL);
	}
	else if (is_redirection(tools->lexer_lst->token))
	{
		parent_node = handle_redir(parent_node, tools);
		if (!parent_node)
			return (NULL);
	}
	else if (tools->lexer_lst->token == T_ARG && cmd_node)
		parse_arg(cmd_node, tools);
	else
		tools->lexer_lst = tools->lexer_lst->next;
	return (parent_node);
}

int	parse_input(t_tools *tools)
{
	t_ast	*cmd_node;
	t_ast	*parent_node;

	cmd_node = NULL;
	parent_node = NULL;
	while (tools->lexer_lst)
	{
		parent_node = process_token(parent_node, cmd_node, tools);
		if (!parent_node && tools->lexer_lst->token != T_ARG)
			return (0);
	}
	tools->tree = parent_node;
	return (1);
}
