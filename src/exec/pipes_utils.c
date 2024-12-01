/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:15:05 by pmolzer           #+#    #+#             */
/*   Updated: 2024/12/01 16:15:39 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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