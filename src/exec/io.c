/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:24 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:34:24 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	here_doc(char *limiter, t_ast *node)
{
	char	*line;
	int		tmp_file_fd;

	tmp_file_fd = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_file_fd == -1)
		msg_error("Failed to open temporary file");
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(line) - 1))
			break ;
		write(tmp_file_fd, line, ft_strlen(line));
		write(tmp_file_fd, "\n", 1);
	}
	close(tmp_file_fd);
	node->file = TEMP_FILE;
}

// TODO: Change so it handles multiple here_docs
/**
 * Sets the input file for the pipeline, handling here_doc
 *
 * @param argv An array of arguments passed to the program.
 * @param exec A pointer to a t_exec structure containing pipeline
 * information.
 */
void	set_infile(t_ast *node)
{
	int	fd;

	if (node->token == T_HEREDOC)
		here_doc(node->file, node);
	if (access(node->file, R_OK) == -1)
		msg_error("Input file access error");
	fd = open(node->file, O_RDONLY);
	if (fd < 0)
		msg_error("Failed to open input file");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/**
 * Sets the output file for the pipeline,
	handling here_doc case for append mode.
 *
 * @param argv The output file path.
 * @param exec A pointer to a t_exec structure
 * containing pipeline information.
 */
void	set_outfile(t_ast *node, bool append_mode)
{
	int	fd;

	if (append_mode)
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(node->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		msg_error("Failed to open output file");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
