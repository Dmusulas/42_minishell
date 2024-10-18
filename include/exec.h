/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:31:16 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/18 14:56:39 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Rewrite errors messages

#ifndef EXEC_H
# define EXEC_H

# include "lexer_parser.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# define ERR_OUTFILE "Outfile error"
# define ERR_INFILE "Infile error"
# define ERR_ACCESS "Access error"
# define ERR_MALLOC "Memory allocation error"
# define ERR_PIPE "Pipe creation error"
# define ERR_FORK "Fork creation error"
# define ERR_EXEC "Child execution error"
# define ERR_FILE "Cannot open file"
# define TEMP_FILE "/tmp/here_doc_12342"

typedef struct s_exec
{
	int		in_fd;
	int		out_fd;
	bool	here_doc;
	bool	is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
	int		cmd_start_position;
}	t_exec;

/* UTILS */
int		msg_error(char *err);
void	restore_stdin_stdout(int saved_stdin, int saved_stdout);
void	save_stdin_stdout(int *saved_stdin, int *saved_stdout);
char	**parse_cmd_args(char *cmd_path, t_ast *node);

/* IO */
void	set_outfile(t_ast *node, bool append_mode);
void	set_infile(t_ast *node);

/* PIPES */
void	handle_pipe_parent(int *fd, int *fd_in);
void	handle_pipe_child(int *fd, int *fd_in, t_ast *node, t_tools *tools);
void	handle_pipes(t_ast *node, t_tools *tools);

/* EXEC */
void	execute_command(t_ast *node, t_tools *tools);
void	fork_and_execute_command(t_ast *node, t_tools *tools);
void	execute_at_path(char *path, t_ast *node, char **envp);
void	execute_external_command(t_ast *node, char **envp);

/* PATH THINGS */
char	*find_cmd(char *paths, char *cmd);
char	*find_path(char **envp);
char	*resolve_relative_path(char *rel_path);
int		is_absolute_or_relative_path(char *cmd);

#endif
