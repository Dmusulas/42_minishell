/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:31:16 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/17 16:53:54 by pmolzer          ###   ########.fr       */
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
void	exec_cmd(t_ast *node, char **envp);
void	fork_and_execute_command(t_ast *node, t_tools *tools);

/* PATH THINGS */
char	*find_cmd(char *paths, char *cmd);
char	*find_path(char **envp);

#endif
