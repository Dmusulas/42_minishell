/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:31:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/14 20:31:14 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(node->left, tools);
	exit(0);
}

void	handle_pipes(t_ast *node, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	t_ast	*current_node;

	fd_in = -1;
	current_node = node;
	while (current_node && current_node->token == T_PIPE)
	{
		if (pipe(fd) == -1)
			msg_error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			msg_error(ERR_FORK);
		else if (pid == 0)
			handle_pipe_child(fd, &fd_in, current_node, tools);
		else
			handle_pipe_parent(fd, &fd_in);
		current_node = current_node->right;
	}
	if (fd_in != -1)
		dup2(fd_in, STDIN_FILENO);
	execute_command(current_node, tools);
	while (wait(NULL) > 0)
		;
}
