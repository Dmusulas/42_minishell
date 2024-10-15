/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/14 13:53:38 by pmolzer          ###   ########.fr       */
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
			exit(EXIT_FAILURE);  // In case exec_cmd fails
		}
		else
		{
			waitpid(pid, &tools->last_exit_status, 0);
			if (WIFEXITED(tools->last_exit_status))
			{
				tools->last_exit_status = WEXITSTATUS(tools->last_exit_status);
				printf("[DEBUG] Command exited with status: %d\n", tools->last_exit_status);
			}
			else if (WIFSIGNALED(tools->last_exit_status))
			{
				tools->last_exit_status = 128 + WTERMSIG(tools->last_exit_status);
				printf("[DEBUG] Command terminated by signal: %d\n", WTERMSIG(tools->last_exit_status));
			}
			printf("[DEBUG] Last exit status after command execution: %d\n", tools->last_exit_status);
		}
	}
}

void	execute_command(t_ast *node, t_tools *tools)
{
	int status;

	if (!node)
		return;
	if (node->token == T_PIPE)
		handle_pipe(node, tools);
	else if (node->token == T_REDIR_IN || node->token == T_REDIR_OUT)
		handle_redirect(node, tools);
	else if (node->token == T_CMD)
	{
		handle_command(node, tools);
		wait(&status);
		if (WIFEXITED(status))
			tools->last_exit_status = WEXITSTATUS(status);
	}
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
		ft_putstr_fd("PATH variable not found\n", STDERR_FILENO);
		exit(127);  // Command not found
	}
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_printf("%s: command not found\n", node->str);
		exit(127);  // Command not found
	}
	cmd_args = parse_cmd_args(cmd_path, node);
	if (!cmd_args)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	printf("[DEBUG] Executing command: %s\n", cmd_path);
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	printf("[DEBUG] Command executed successfully: %s\n", cmd_path);
}
