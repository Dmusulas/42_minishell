/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:31:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/05 11:33:15 by pmolzer          ###   ########.fr       */
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
	if (tools->last_exit_status != 0)  // Add this check
		exit(tools->last_exit_status);
	exit(tools->last_exit_status);
}

static int is_last_command_grep(t_ast *node)
{
    if (!node || !node->str)
        return (0);
    return (ft_strcmp(node->str, "grep") == 0);
}

void	handle_pipes(t_ast *node, t_tools *tools)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	t_ast	*current_node;
	t_ast	*last_cmd;
	int		status;
	int		exit_code;

	fd_in = -1;
	current_node = node;
	while (current_node && current_node->token == T_PIPE)
	{
		if (pipe(fd) == -1)
		{
			tools->last_exit_status = 1;
			return;
		}
		pid = fork();
		if (pid == -1)
		{
			tools->last_exit_status = 1;
			close(fd[0]);
			close(fd[1]);
			return;
		}
		else if (pid == 0)
			handle_pipe_child(fd, &fd_in, current_node, tools);
		else
		{
			handle_pipe_parent(fd, &fd_in);
			current_node = current_node->right;
		}
	}

	// Handle last command
	pid = fork();
	if (pid == 0)
	{
		if (current_node->token == T_REDIR_IN)
			set_infile(current_node, tools);
		if (fd_in != -1)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		execute_command(current_node, tools);
		exit(tools->last_exit_status);
	}
	
	if (fd_in != -1)
		close(fd_in);

	// Store last command node before wait loop
	last_cmd = current_node;

	// Wait for all child processes
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (is_last_command_grep(last_cmd) && exit_code == 2)
				tools->last_exit_status = 1;
			else
				tools->last_exit_status = exit_code;
		}
	}
}
