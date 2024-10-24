/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/24 12:41:00 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "libft.h"
#include "minishell.h"

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
static void	handle_io_redirection(t_ast *node, t_tools *tools)
{
	int	saved_stdin;
	int	saved_stdout;

	save_stdin_stdout(&saved_stdin, &saved_stdout);
	if (node->token == T_REDIR_IN || node->token == T_HEREDOC)
		set_infile(node, tools);
	if (node->token == T_REDIR_OUT)
		set_outfile(node, false, tools);
	if (node->token == T_APPEND)
		set_outfile(node, true, tools);
	execute_command(node->left, tools);
	restore_stdin_stdout(saved_stdin, saved_stdout);
}
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
				ft_putstr_fd(node->str, 2);
				ft_putendl_fd(": No such file or directory", 2);
				exit(127);  // Changed from 1 to 127 for "command not found"
			}
			execute_at_path(cmd_path, node, envp, tools);
		}
	}
	path_var = find_path(envp);
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_putstr_fd(node->str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);  // Changed from 1 to 127 for "command not found"
	}
	execute_at_path(cmd_path, node, envp, tools);
}

/**
 * Executes the command or operation represented by the given AST node.
 * Depending on the token, it either handles pipes, redirects input/output,
 * or executes a single command. It restores standard input/output afterward.
 *
 * @param node The AST node representing a command, pipe, or redirection.
 * @param tools Struct containing necessary tools for execution.
 */
void	execute_command(t_ast *node, t_tools *tools)
{
	if (!node)
		return ;
	if (node->token == T_PIPE)
	{
		handle_pipes(node, tools);
		return ;
	}
	if (token_check(node->token))
	{
		handle_io_redirection(node, tools);
		return ;
	}
	execute_single_command(node, tools);
}
