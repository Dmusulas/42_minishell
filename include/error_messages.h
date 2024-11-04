/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:14:12 by pmolzer           #+#    #+#             */
/*   Updated: 2024/11/04 15:25:59 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# include "lexer_parser.h"

typedef enum e_error_type
{
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION_DENIED,
	ERR_TOO_MANY_ARGS,
	ERR_NUMERIC_ARG_REQUIRED,
	ERR_HOME_NOT_SET,
	ERR_OLDPWD_NOT_SET,
	ERR_INVALID_IDENTIFIER,
	ERR_MALLOC_FAIL,
	ERR_PIPE_FAIL,
	ERR_FORK_FAIL,
	ERR_DUP2_FAIL,
	ERR_EXECVE_FAIL,
	ERR_OUTFILE,
	ERR_INFILE,
	ERR_ACCESS,
	ERR_MALLOC,
	ERR_PIPE,
	ERR_FORK,
	ERR_EXEC,
	ERR_FILE,
	ERR_IS_A_DIRECTORY,
}	t_error_type;

# define ERR_SYNTAX_MSG "syntax error near unexpected token"
# define ERR_CMD_NOT_FOUND_MSG "command not found"
# define ERR_NO_SUCH_FILE_MSG "No such file or directory"
# define ERR_IS_A_DIRECTORY_MSG "is a directory"
# define ERR_PERMISSION_DENIED_MSG "Permission denied"
# define ERR_TOO_MANY_ARGS_MSG "too many arguments"
# define ERR_NUMERIC_ARG_REQUIRED_MSG "numeric argument required"
# define ERR_HOME_NOT_SET_MSG "HOME not set"
# define ERR_OLDPWD_NOT_SET_MSG "OLDPWD not set"
# define ERR_INVALID_IDENTIFIER_MSG "not a valid identifier"
# define ERR_MALLOC_FAIL_MSG "memory allocation failed"
# define ERR_PIPE_FAIL_MSG "pipe creation failed"
# define ERR_FORK_FAIL_MSG "fork failed"
# define ERR_DUP2_FAIL_MSG "dup2 failed"
# define ERR_EXECVE_FAIL_MSG "execve failed"
# define ERR_OUTFILE_MSG "Outfile error"
# define ERR_INFILE_MSG "Infile error"
# define ERR_ACCESS_MSG "Access error"
# define ERR_MALLOC_MSG "Memory allocation error"
# define ERR_PIPE_MSG "Pipe creation error"
# define ERR_FORK_MSG "Fork creation error"
# define ERR_EXEC_MSG "Child execution error"
# define ERR_FILE_MSG "Cannot open file"

int		ft_error(t_error_type err_type, t_tools *tools);

#endif
