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

/**
 * Redirects the old file descriptor to the new file descriptor
 * and closes the old one.
 *
 * @param old_fd The file descriptor to be redirected.
 * @param new_fd The file descriptor to redirect to.
 */
static void	redirect_fds(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

/**
 * Sets up the pipes and redirects file descriptors for a specific
 * command in the pipeline.
 *

 * @param exec A pointer to a t_exec structure containing
 * pipeline information.
 * @param fd An array of two integers representing the pipe file descriptors.
 * @param i The index of the current command in the pipeline.
 */
static void	setup_pipes(t_exec *exec, int *fd, int i)
{
	if (i == 0)
		redirect_fds(exec->in_fd, STDIN_FILENO);
	if (i == exec->cmd_count - 1)
		redirect_fds(exec->out_fd, STDOUT_FILENO);
	if (i < exec->cmd_count - 1)
	{
		close(fd[0]);
		redirect_fds(fd[1], STDOUT_FILENO);
	}
}

/**
 * Executes a command using execve, replacing the current process
 * image with a new process image.
 *

 * @param exec A pointer to a t_exec structure containing
 * pipeline information.
 * @param envp An array of environment variables.
 * @param i The index of the command to execute in the pipeline.
 */
void	exec_cmd(t_ast *node, char **envp)
{
	if (!access(node->str, X_OK))
		execve(node->str, &node->left->str, envp);
	msg_error("Execve failed", NULL);
	exit(EXIT_FAILURE);
}

/**
 * Handles the creation and setup of a child process for executing
 * a command in the pipeline.
 *

 * @param exec A pointer to a t_exec structure containing
 * pipeline information.
 * @param envp An array of environment variables.
 * @param i The index of the current command in the pipeline.
 */
static void	child_process(t_exec *exec, char **envp, int i, int *fd_in)
{
	int		fd[2];
	pid_t	pid;

	if (i < exec->cmd_count - 1 && pipe(fd) == -1)
		msg_error(ERR_PIPE, exec);
	pid = fork();
	if (pid == -1)
		msg_error(ERR_FORK, exec);
	else if (pid == 0)
	{
		if (i > 0)
			redirect_fds(*fd_in, STDIN_FILENO);
		setup_pipes(exec, fd, i);
		execute_cmd(exec, envp, i);
	}
	else
	{
		if (i > 0)
			close(*fd_in);
		if (i < exec->cmd_count - 1)
		{
			close(fd[1]);
			*fd_in = fd[0];
		}
	}
}
