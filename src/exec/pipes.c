/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:31:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/24 12:31:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "exec.h"
#include "lexer_parser.h"

void	handle_pipe_parent(int *fd, int *fd_in)
{
	close(fd[1]);
	if (*fd_in != -1)
		close(*fd_in);
	*fd_in = fd[0];
}

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
	exit(tools->last_exit_status);  // Changed from exit(1) to exit with proper status
}

void	handle_pipes(t_ast *node, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	t_ast	*current_node;
	int		status;

	fd_in = -1;
	current_node = node;
	while (current_node && current_node->token == T_PIPE)
	{
		if (pipe(fd) == -1)
			ft_error(ERR_PIPE, tools);
		pid = fork();
		if (pid == -1)
			ft_error(ERR_FORK, tools);
		else if (pid == 0)
			handle_pipe_child(fd, &fd_in, current_node, tools);
		else
			handle_pipe_parent(fd, &fd_in);
		current_node = current_node->right;
	}
	pid = fork();
	if (pid == 0)
	{
		if (current_node->token == T_REDIR_IN)
			set_infile(current_node, tools);
		if (fd_in != -1)
			dup2(fd_in, STDIN_FILENO);
		execute_command(current_node, tools);
		exit(tools->last_exit_status);
	}
	if (fd_in != -1)
		close(fd_in);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			tools->last_exit_status = WEXITSTATUS(status);
	}
}
