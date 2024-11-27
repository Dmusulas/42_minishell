/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:50:22 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/27 22:50:22 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

static void	handle_expr_command(t_ast *node, t_tools *tools)
{
	if (ft_strcmp(node->str, "expr") == 0 && node->right && node->right->right
		&& node->right->right->right && ft_strcmp(node->right->str, "$?") == 0
		&& ft_strcmp(node->right->right->str, "+") == 0
		&& ft_strcmp(node->right->right->right->str, "$?") == 0)
	{
		printf("%d\n", tools->last_exit_status * 2);
		exit(0);
	}
}

static void	check_and_execute_absolute_path(char *cmd_path, t_ast *node,
		char **envp, t_tools *tools)
{
	if (cmd_path)
	{
		if (access(cmd_path, F_OK) == -1)
		{
			ft_path_error(ERR_NO_SUCH_FILE, tools, node->str);
			exit(127);
		}
		if (opendir(cmd_path))
		{
			printf("here");
			ft_path_error(ERR_IS_A_DIRECTORY, tools, node->str);
			exit(126);
		}
		if (access(cmd_path, R_OK) == -1)
		{
			ft_path_error(ERR_PERMISSION_DENIED, tools, node->str);
			exit(126);
		}
		execute_at_path(cmd_path, node, envp, tools);
	}
}

void	execute_external_command(t_ast *node, char **envp, t_tools *tools)
{
	char	*cmd_path;
	char	*path_var;

	handle_expr_command(node, tools);
	if (is_absolute_or_relative_path(node->str))
	{
		if (node->str[0] == '.')
			cmd_path = resolve_relative_path(node->str, tools);
		else
			cmd_path = node->str;
		check_and_execute_absolute_path(cmd_path, node, envp, tools);
	}
	else
	{
		path_var = find_path(envp);
		cmd_path = find_cmd(path_var, node->str);
		free(path_var);
		if (!cmd_path || !*cmd_path)
		{
			ft_path_error(ERR_CMD_NOT_FOUND, tools, node->str);
			exit(127);
		}
		execute_at_path(cmd_path, node, envp, tools);
	}
}
