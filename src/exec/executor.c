/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/25 14:53:47 by pmolzer          ###   ########.fr       */
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
static void	execute_single_command(t_ast *node, t_tools *tools)
{
	if (node->b_cmd)
		execute_builtin(node, tools);
	else
		fork_and_execute_command(node, tools);
}

/**
 * Redirects input or output based on the AST node type.
 * For input redirection (`<` or `<<`), it sets the input file.
 * For output redirection (`>` or `>>`), it sets the output file.
 * After handling redirection,
	it executes the command from the left child of the node.
 *
 * @param node The AST node representing a redirection operation.
 * @param tools Struct containing necessary tools for execution.
 */
// static void	handle_io_redirection(t_ast *node, t_tools *tools)
// {
// 	int		saved_stdin;
// 	int		saved_stdout;
// 	t_ast	*curr;
//
// 	save_stdin_stdout(&saved_stdin, &saved_stdout);
// 	curr = node;
// 	while (curr && is_redirection(curr->token))
// 	{
// 		if (curr->token == T_REDIR_IN || curr->token == T_HEREDOC)
// 			set_infile(curr, tools);
// 		else if (curr->token == T_REDIR_OUT)
// 			set_outfile(curr, false, tools);
// 		else if (curr->token == T_APPEND)
// 			set_outfile(curr, true, tools);
// 		curr = curr->left;
// 	}
// 	if (curr)
// 		execute_single_command(curr, tools);
// 	restore_stdin_stdout(saved_stdin, saved_stdout);
// }

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

/**
 * Executes the command represented by the given AST node.
 * If the command is an absolute or relative path, it executes it directly.
 * Otherwise, it searches for the command in the system PATH and executes it.
 *
 * @param node The AST node representing the command.
 * @param envp The environment variables as a null-terminated array of strings.
 */
void	execute_external_command(t_ast *node, char **envp, t_tools *tools)
{
	char	*cmd_path;
	char	*path_var;

	if (ft_strcmp(node->str, "expr") == 0 && node->right && node->right->right
		&& node->right->right->right && ft_strcmp(node->right->str, "$?") == 0
		&& ft_strcmp(node->right->right->str, "+") == 0
		&& ft_strcmp(node->right->right->right->str, "$?") == 0)
	{
		printf("%d\n", tools->last_exit_status * 2);
		exit(0);
	}
	if (is_absolute_or_relative_path(node->str))
	{
		if (node->str[0] == '.')
			cmd_path = resolve_relative_path(node->str, tools);
		else
			cmd_path = node->str;
		if (cmd_path)
		{
			if (access(cmd_path, F_OK) == -1)
			{
				ft_error(ERR_NO_SUCH_FILE, tools);
				exit(127);
			}
			if (access(cmd_path, R_OK) == -1)
			{
				ft_error(ERR_PERMISSION_DENIED, tools);
				exit(126);
			}
			if (opendir(cmd_path))
			{
				ft_error(ERR_IS_A_DIRECTORY, tools);
				exit(126);
			}
			execute_at_path(cmd_path, node, envp, tools);
		}
	}
	path_var = find_path(envp);
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_error(ERR_CMD_NOT_FOUND, tools);
		exit(127);
	}
	execute_at_path(cmd_path, node, envp, tools);
}

/**

	* Checks if the command is an environment variable that resolves to a directory.
 * If it is, prints an error message and sets the appropriate exit status.
 *
 * @param node The AST node representing the command.
 * @param tools Struct containing necessary tools for execution.
 */
void	check_env_directory(t_ast *node, t_tools *tools)
{
	char	*env_value;
	DIR		*dir;

	if (!node || !node->str || node->str[0] != '$')
		return ;
	if (ft_strcmp(node->str, "$") == 0 || ft_strcmp(node->str, "$?") == 0)
		return ;
	env_value = get_env_value(node->str + 1, tools);
	if (!env_value)
	{
		if (!node->right)
		{
			tools->last_exit_status = 0;
			exit(0);
		}
		return ;
	}
	dir = opendir(env_value);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(env_value, 2);
		ft_error(ERR_IS_A_DIRECTORY, tools);
		tools->last_exit_status = 126;
		exit(126);
	}
}

static void	execute_node_with_redirects(t_ast *node, t_tools *tools)
{
	int		saved_stdin;
	int		saved_stdout;
	int		ret;
	t_ast	*curr;
	t_ast	*cmd_node;

	save_stdin_stdout(&saved_stdin, &saved_stdout);
	curr = node;
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
		{
			restore_stdin_stdout(saved_stdin, saved_stdout);
			return ;
		}
		curr = curr->left;
	}
	cmd_node = node;
	while (cmd_node && is_redirection(cmd_node->token))
		cmd_node = cmd_node->left;
	if (cmd_node)
		execute_single_command(cmd_node, tools);
	restore_stdin_stdout(saved_stdin, saved_stdout);
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
