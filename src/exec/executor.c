/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:25:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

/**
 * Handles the execution of a command represented by the given AST node.
 * If the command is a built-in command, it is executed directly. Otherwise,
 * a new process is forked, and the external command is executed.
 *
 * @param node The AST node representing a command.
 * @param tools Struct containing necessary tools for execution.
 */
void	execute_single_command(t_ast *node, t_tools *tools)
{
	if (node->b_cmd)
		execute_builtin(node, tools);
	else
		fork_and_execute_command(node, tools);
}

/**
 * Executes a command at the given path.
 *
 * @param path The command path (absolute or relative).
 * @param node The AST node representing the command.
 * @param envp The environment variables.
 * @return void, exits on failure.
 */
void	execute_at_path(char *path, t_ast *node, char **envp, t_tools *tools)
{
	char	**cmd_args;
	int		exec_status;

	cmd_args = parse_cmd_args(path, node);
	exec_status = execve(path, cmd_args, envp);
	if (exec_status == -1)
	{
		ft_error(ERR_EXECVE_FAIL, tools);
		exit(126);
	}
	tools->last_exit_status = exec_status;
}

void	check_env_directory(t_ast *node, t_tools *tools)
{
	char	*env_value;
	DIR		*dir;

	if (!node || !node->str || node->str[0] != '$')
		return ;
	if (is_special_env_var(node->str))
		return ;
	env_value = get_env_value(node->str + 1, tools);
	if (!env_value)
	{
		handle_empty_env(node, tools);
		return ;
	}
	dir = opendir(env_value);
	if (dir)
	{
		closedir(dir);
		handle_directory_error(env_value, tools);
	}
}

/**
 * Executes the command or operation represented by the given AST node.
 * Depending on the token, it either handles pipes, redirects input/output,
 * or executes a single command.
 *
 * @param node The AST node representing a command, pipe, or redirection.
 * @param tools Struct containing necessary tools for execution.
 */
void	execute_command(t_ast *node, t_tools *tools)
{
	char	*env_value;

	set_inactive_signals();
	if (!node)
		return ;
	if (node->token == T_PIPE)
	{
		handle_pipes(node, tools);
		return ;
	}
	if (node->str && node->str[0] == '$')
	{
		if (ft_strcmp(node->str, "$") != 0 && ft_strcmp(node->str, "$?") != 0)
		{
			env_value = get_env_value(node->str + 1, tools);
			if (!env_value && node->right)
			{
				execute_command(node->right, tools);
				return ;
			}
		}
	}
	check_env_directory(node, tools);
	execute_node_with_redirects(node, tools);
	set_active_signals();
}
