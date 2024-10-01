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
#include "libft.h"
#include <stdlib.h>

/**
 * Sets up a pipe and forks a process to handle reading input for
 * the here_doc functionality.
 *
 * @param limiter A string used to determine when to stop reading user input.
 * @param exec A pointer to a t_exec structure containing pipeline
 * information.
 */
void	here_doc(char *limiter, t_exec *exec)
{
	char	*line;
	int		tmp_file_fd;

	tmp_file_fd = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_file_fd == -1)
		msg_error("Failed to open temporary file", exec);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		write(tmp_file_fd, line, ft_strlen(line));
		write(tmp_file_fd, "\n", 1);
		free(line);
	}
	close(tmp_file_fd);
	exec->in_fd = open(TEMP_FILE, O_RDONLY);
	unlink(TEMP_FILE);
}

/**
 * Sets the input file for the pipeline, handling here_doc
 *
 * @param argv An array of arguments passed to the program.
 * @param exec A pointer to a t_exec structure containing pipeline
 * information.
 */
void	set_infile(char **argv, t_exec *exec)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		here_doc(argv[2], exec);
		exec->here_doc = true;
		exec->cmd_count -= 1;
		exec->cmd_start_position += 1;
	}
	else
	{
		if (access(argv[1], R_OK) == -1)
			msg_error(ERR_ACCESS, exec);
		exec->in_fd = open(argv[1], O_RDONLY);
		if (exec->in_fd < 0)
			msg_error(ERR_INFILE, exec);
	}
}

/**
 * Sets the output file for the pipeline,
	handling here_doc case for append mode.
 *
 * @param argv The output file path.
 * @param exec A pointer to a t_exec structure
 * containing pipeline information.
 */
void	set_outfile(char *argv, t_exec *exec)
{
	if (exec->here_doc)
		exec->out_fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->out_fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->out_fd < 0)
		msg_error(ERR_OUTFILE, exec);
}
