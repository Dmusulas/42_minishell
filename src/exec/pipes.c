/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:31:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 20:12:32 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "exec.h"
#include "lexer_parser.h"

/**
 * Closes the write end of the pipe and the current input file descriptor if
 * it is not -1, and sets the current input file descriptor to the read end of
 * the pipe. This is used in the parent process after forking to set up the
 * input redirection.
 *
 * @param fd A pointer to an array of two file descriptors, where fd[0] is the
 * read end of the pipe and fd[1] is the write end.
 * @param fd_in A pointer to the current input file descriptor.
 */
void	handle_pipe_parent(int *fd, int *fd_in)
{
	close(fd[1]);
	if (*fd_in != -1)
		close(*fd_in);
	*fd_in = fd[0];
}

/**
 * Handles the execution of a command in a pipeline as a child process.
 *
 * Closes the read end of the pipe and sets up the input file descriptor
 * if there is a redirection token in the AST node. If there is another
 * command in the pipeline, it duplicates the write end of the pipe to
 * stdout and closes the write end. It then executes the command and
 * exits with the exit status of the command.
 */
void	handle_pipe_child(int *fd, int *fd_in, t_ast *node, t_tools *tools)
{
	close(fd[0]);
	if (node->token == T_REDIR_IN || node->token == T_HEREDOC)
		set_infile(node, tools);
	if (node->right)
	{
		dup2(fd[1], STDOUT_FILENO);
	}
	close(fd[1]);
	if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	execute_command(node->left, tools);
	if (tools->last_exit_status != 0)
		exit(tools->last_exit_status);
	exit(tools->last_exit_status);
}

// /**
//  * Checks if the last command in the pipe sequence is 'grep'.
//  * This is needed because grep doesn't exit with 0 if no match is found,
//  * even though it is a successful command.
//  */
// static int	is_last_command_grep(t_ast *node)
// {
// 	if (!node || !node->str)
// 		return (0);
// 	return (ft_strcmp(node->str, "grep") == 0);
// }

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
	while ((waiting_pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (waiting_pid == last_pid)
				tools->last_exit_status = exit_code;
		}
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

	* for all child processes to complete. The last command in the series is executed
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
