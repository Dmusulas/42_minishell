/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/15 12:05:19 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "libft.h"
#include "minishell.h"

/**
 * Handles input redirection for the given AST node.
 * It sets the appropriate input file based on the type of redirection token
 * and then recursively executes the left child of the node.
 */
static void	handle_redirect(t_ast *node, t_tools *tools)
{
	if (node->token == T_REDIR_IN || node->token == T_HEREDOC)
		set_infile(node);
	if (node->token == T_REDIR_OUT)
		set_outfile(node, false);
	if (node->token == T_APPEND)
		set_outfile(node, true);
	execute_command(node->left, tools);
}

/**
 * Handles the execution of a command represented by the given AST node.
 * It checks if the node is a built-in command and executes it accordingly,
 * or forks a new process to execute the command.
 */
static void	handle_command(t_ast *node, t_tools *tools)
{
	if (node->b_cmd)
		execute_builtin(node, tools);
	else
		fork_and_execute_command(node, tools);
}

/**
 * Executes a command represented by the given AST node.
 * It finds the command's path, prepares the command arguments,
 * and calls execve to execute the command in a new process.
 * If the command cannot be found or execution fails, it exits with an error.
 */
void	exec_cmd(t_ast *node, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	char	*path_var;

	path_var = find_path(envp);
	if (!path_var)
	{
		ft_putendl_fd("PATH variable not found", STDERR_FILENO);
		exit(127);
	}
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_printf("%s: command not found\n", node->str);
		free(cmd_path);
		exit(127);
	}
	cmd_args = parse_cmd_args(cmd_path, node);
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("Execve failed");
		exit(126);
	}
}

/**
 * Executes a command represented by the given AST node.
 * It saves the current standard input and output, handles pipes,
 * redirects, or commands based on the node's token, and restores
 * the standard input and output afterwards.
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
		handle_redirect(node, tools);
		return ;
	}
	handle_command(node, tools);
}
