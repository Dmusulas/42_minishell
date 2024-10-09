/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:35:54 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

static void	handle_pipe(t_ast *node, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		msg_error(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		msg_error(ERR_FORK);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(node->left, tools);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_command(node->right, tools);
	}
}

static void	handle_redirect(t_ast *node, t_tools *tools)
{
	if (node->token == T_REDIR_IN)
		set_infile(node);
	else if (node->token == T_REDIR_OUT)
		set_outfile(node, false);
	else if (node->token == T_APPEND)
		set_outfile(node, true);
	execute_command(node->left, tools);
}

static void	handle_command(t_ast *node, t_tools *tools)
{
	if (node->b_cmd)
		execute_builtin(node, tools);
	else
		exec_cmd(node, list_to_array(tools->envp));
}

void	execute_command(t_ast *node, t_tools *tools)
{
	if (!node)
		return ;
	if (node->token == T_PIPE)
		handle_pipe(node, tools);
	else if (node->token == T_REDIR_IN || node->token == T_REDIR_OUT)
		handle_redirect(node, tools);
	else if (node->token == T_CMD)
		handle_command(node, tools);
}

static char	**parse_cmd_args(t_ast *node)
{
	int		arg_count;
	t_ast	*current;
	char	**args;

	arg_count = 0;
	current = node->right;
	while (current)
	{
		arg_count++;
		current = current->right;
	}
	args = (char **)malloc(sizeof(char *) * (arg_count + 2));
	if (!args)
		return (NULL);
	args[arg_count + 1] = NULL;
	args[0] = ft_strdup(node->str);
	current = node->right;
	arg_count = 1;
	while (current != NULL)
	{
		args[arg_count] = ft_strdup(current->str);
		current = current->right;
		arg_count++;
	}
	return (args);
}

void	exec_cmd(t_ast *node, char **envp)
{
	char	**cmd_args;

	if (node->right)
		cmd_args = parse_cmd_args(node->right);
	if (!access(node->str, X_OK))
		execve(node->str, cmd_args, envp);
	else
	{
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
}
