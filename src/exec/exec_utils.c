/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:32:35 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 14:47:47 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

/**
 * Forks a new process to execute a command represented by the given AST node.
 * In the child process, it calls exec_cmd to execute the command with the
 * environment variables. In the parent process, it waits for the child to
 * finish and updates the last exit status based on the child's exit status.
 * If the child process exits normally, the last exit status is set to the
 * exit code of the child. If the child process does not exit normally, the
 * last exit status is set to 1, indicating an error occurred during execution.
 */
void	fork_and_execute_command(t_ast *node, t_tools *tools)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_error(ERR_FORK, tools);
	}
	else if (pid == 0)
	{
		execute_external_command(node, list_to_array(tools->envp), tools);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			tools->last_exit_status = WEXITSTATUS(status);
		else
			tools->last_exit_status = 1;
	}
}

char	**parse_cmd_args(char *cmd_path, t_ast *node)
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

void	save_stdin_stdout(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
