/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:31:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:15:36 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"

/**
 * Waits for all child processes to finish and updates the last exit status
 * of the tools struct. If the last command was grep and it exited with a
 * status of 2, sets the last exit status to 1.
 *
 * @param last_cmd The last command in the pipeline.
 * @param tools    Pointer to a t_tools struct.
 */
static void	wait_for_children(t_tools *tools)
{
	int	status;
	int	exit_code;
	int	last_pid;
	int	waiting_pid;

	last_pid = tools->last_pid;
	waiting_pid = wait(&status);
	while (waiting_pid > 0)
	{
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (waiting_pid == last_pid)
				tools->last_exit_status = exit_code;
		}
		waiting_pid = wait(&status);
	}
}

/**
 * Executes the last command in a series of piped commands.
 * Forks a new process where it sets up input redirection if necessary,
 * duplicates the input file descriptor to stdin, and executes the command.
 * The last exit status is set based on the command's execution result.
 *
 * @param node The AST node representing the command to execute.
 * @param fd_in The file descriptor for input redirection. If -1,
	no redirection is needed.
 * @param tools Struct containing necessary tools and state for execution.
 */
static void	execute_last_command(t_ast *node, int fd_in, t_tools *tools)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (node->token == T_REDIR_IN)
			set_infile(node, tools);
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		execute_command(node, tools);
		exit(tools->last_exit_status);
	}
	tools->last_pid = pid;
}

/**
 * Creates a pipe and forks a child process to handle the command execution.
 * In the child process, it returns the child's process id.
 * If the pipe creation or fork fails, it sets the last exit status to 1
 * and returns -1.
 *
 * @param fd An array of two file descriptors, where fd[0] will be the read
 * end of the pipe and fd[1] will be the write end.
 * @param tools Struct containing necessary tools and state for execution.
 * @return The child's process id on success, -1 on failure.
 */
static int	create_pipe_and_fork(int fd[2], t_tools *tools)
{
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		tools->last_exit_status = 1;
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		tools->last_exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	return (pid);
}

/**
 * Handles the execution of a series of piped commands represented by an AST.
 * For each pipe node, it creates a new pipe and forks a child process to handle
 * the command execution. In the child process,
	it sets up the necessary input and
 * output file descriptors and executes the command. In the parent process, it
 * manages the file descriptors for piping, advances to the next command,
	and waits
	* for all child processes to complete.
	* The last command in the series is executed
 * separately, ensuring proper stdin redirection. The function updates the exit
 * status in the tools structure based on the execution results.
 *
 * @param node The AST node representing the start of the pipe sequence.
 * @param tools Struct containing necessary tools and state for execution.
 */
void	handle_pipes(t_ast *node, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;
	t_ast	*current_node;
	int		fd_in;

	fd_in = -1;
	current_node = node;
	while (current_node && current_node->token == T_PIPE)
	{
		pid = create_pipe_and_fork(fd, tools);
		if (pid == -1)
			return ;
		else if (pid == 0)
			handle_pipe_child(fd, &fd_in, current_node, tools);
		else
		{
			handle_pipe_parent(fd, &fd_in);
			current_node = current_node->right;
		}
	}
	execute_last_command(current_node, fd_in, tools);
	if (fd_in != -1)
		close(fd_in);
	wait_for_children(tools);
}
