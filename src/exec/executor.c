/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/12 14:11:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "libft.h"
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
	pid_t	pid;

	if (node->b_cmd)
	{
		// Execute builtin in the current process
		execute_builtin(node, tools);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			exec_cmd(node, list_to_array(tools->envp));
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
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

static char	**parse_cmd_args(char *cmd_path, t_ast *node)
{
	int		arg_count;
	t_ast	*current;
	char	**args;

	arg_count = 1;
	current = node->right;
	while (current)
	{
		arg_count++;
		current = current->right;
	}
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	args[arg_count] = NULL;
	args[0] = ft_strdup(cmd_path);
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
	char	*cmd_path;
	char	*path_var;

	path_var = find_path(envp);
	if (!path_var)
	{
		perror("PATH variable not found");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_printf("%s: command not found\n", node->str);
		free(cmd_path);
	}
	cmd_args = parse_cmd_args(cmd_path, node);
	ft_printf("Command Path: %s\n", cmd_path);
	if (execve(cmd_path, cmd_args, envp) == -1)
		perror("Execve failed");
}
