/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:24 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 14:43:22 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

/**
 * Sets up a pipe and forks a process to handle reading input for
 * the here_doc functionality.
 *
 * @param limiter A string used to determine when to stop reading user input.
 * @param exec A pointer to a t_exec structure containing pipeline
 * information.
 */
void	here_doc(char *limiter, t_ast *node, t_tools *tools)
{
	char	*line;
	int		tmp_file_fd;

	tmp_file_fd = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_file_fd == -1)
		ft_error(ERR_PIPE_FAIL, tools);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		write(tmp_file_fd, line, ft_strlen(line));
		write(tmp_file_fd, "\n", 1);
		free(line);
	}
	close(tmp_file_fd);
	node->file = TEMP_FILE;
}

/**
 * Sets the input file for the pipeline, handling here_doc if necessary.
 * It redirects stdin to the specified input file and restores
 * it after execution.
 */
int	set_infile(t_ast *node, t_tools *tools)
{
	int	fd;

	if (node->token == T_HEREDOC)
		here_doc(node->file, node, tools);
	if (access(node->file, F_OK) == -1)
	{
		tools->last_exit_status = 1;
		ft_path_error(ERR_NO_SUCH_FILE, tools, node->file);
		return (1);
	}
	if (access(node->file, R_OK) == -1)
	{
		tools->last_exit_status = 1;
		ft_path_error(ERR_PERMISSION_DENIED, tools, node->file);
		return (1);
	}
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
		ft_error(ERR_NO_SUCH_FILE, tools);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error(ERR_DUP2_FAIL, tools);
	close(fd);
	return (0);
}

/**
 * Sets the output file for the pipeline. It redirects stdout to the specified
 * output file and supports append mode if needed.
 * Restores stdout after execution.
 */
int	set_outfile(t_ast *node, bool append_mode, t_tools *tools)
{
	int	fd;
	int	new_fd;

	if (append_mode)
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(node->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		tools->last_exit_status = 1;
		ft_error(ERR_PERMISSION_DENIED, tools);
		return (1);
	}
	new_fd = dup2(fd, STDOUT_FILENO);
	if (new_fd == -1)
		ft_error(ERR_DUP2_FAIL, tools);
	close(fd);
	return (0);
}
