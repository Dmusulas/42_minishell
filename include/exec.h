/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:31:16 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:32:22 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

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
# define TEMP_FILE "/tmp/here_doc_12342"

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_exec
{
	int		in_fd;
	int		out_fd;
	t_bool	here_doc;
	t_bool	is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
	int		cmd_start_position;
}	t_exec;

void	msg_error(char *err, t_exec *exec);
t_exec	*init_exec(int argc);
void	free_exec(t_exec *exec);
void	set_outfile(char *argv, t_exec *exec);
void	set_infile(char **argv, t_exec *exec);
char	**parse_cmds(t_exec *exec, char **argv, char **envp);
char	***parse_args(t_exec *exec, char **argv);
void	ft_exec(t_exec *exec, char **envp);
void	free_2darray(char **array);

#endif
