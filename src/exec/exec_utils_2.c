/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:19:13 by pmolzer           #+#    #+#             */
/*   Updated: 2024/12/01 16:24:03 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

static int	handle_redirections(t_ast *curr, t_tools *tools)
{
	int	ret;

	ret = 0;
	while (curr && curr->left && is_redirection(curr->left->token))
	{
		if (curr->left->token == T_REDIR_IN || curr->left->token == T_HEREDOC)
			ret = set_infile(curr->left, tools);
		else if (curr->left->token == T_REDIR_OUT)
			ret = set_outfile(curr->left, false, tools);
		else if (curr->left->token == T_APPEND)
			ret = set_outfile(curr->left, true, tools);
		if (ret)
			return (ret);
		curr = curr->left;
	}
	return (ret);
}

static t_ast	*find_command_node(t_ast *node)
{
	t_ast	*cmd_node;

	cmd_node = node;
	while (cmd_node && is_redirection(cmd_node->token))
		cmd_node = cmd_node->left;
	return (cmd_node);
}

void	execute_node_with_redirects(t_ast *node, t_tools *tools)
{
	int		saved_stdin;
	int		saved_stdout;

	save_stdin_stdout(&saved_stdin, &saved_stdout);
	if (handle_redirections(node, tools))
	{
		restore_stdin_stdout(saved_stdin, saved_stdout);
		return ;
	}
	if (find_command_node(node))
		execute_single_command(find_command_node(node), tools);
	restore_stdin_stdout(saved_stdin, saved_stdout);
}
