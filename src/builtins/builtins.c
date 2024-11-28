/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/11/05 13:23:48 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

int	execute_cd(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*arg_node;
	int		status_result;

	status_result = 0;
	arg_node = cmd_node->right;
	if (arg_node)
		status_result = ft_cd(arg_node->str, tools);
	else
		status_result = ft_cd(NULL, tools);
	return (status_result);
}

void	execute_builtin(t_ast *cmd_node, t_tools *tools)
{
	int	status_result;

	status_result = 0;
	if (ft_strcmp(cmd_node->str, "echo") == 0)
		status_result = ft_echo(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "cd") == 0)
		status_result = execute_cd(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "pwd") == 0)
		status_result = ft_pwd(tools);
	else if (ft_strcmp(cmd_node->str, "export") == 0)
		status_result = ft_export(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "unset") == 0)
		status_result = ft_unset(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "env") == 0)
		status_result = ft_env(tools);
	else if (ft_strcmp(cmd_node->str, "exit") == 0)
		status_result = ft_exit(cmd_node, tools);
	tools->last_exit_status = status_result;
}
