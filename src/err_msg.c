/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:22:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/06 15:30:45 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "libft.h"
#include "minishell.h"

void	error_extension(t_error_type err_type)
{
	if (err_type == ERR_PIPE_FAIL)
		ft_putstr_fd(ERR_PIPE_FAIL_MSG, STDERR_FILENO);
	else if (err_type == ERR_FORK_FAIL)
		ft_putstr_fd(ERR_FORK_FAIL_MSG, STDERR_FILENO);
	else if (err_type == ERR_DUP2_FAIL)
		ft_putstr_fd(ERR_DUP2_FAIL_MSG, STDERR_FILENO);
	else if (err_type == ERR_OUTFILE)
		ft_putstr_fd(ERR_OUTFILE_MSG, STDERR_FILENO);
	else if (err_type == ERR_INFILE)
		ft_putstr_fd(ERR_INFILE_MSG, STDERR_FILENO);
	else if (err_type == ERR_ACCESS)
		ft_putstr_fd(ERR_ACCESS_MSG, STDERR_FILENO);
	else if (err_type == ERR_MALLOC)
		ft_putstr_fd(ERR_MALLOC_MSG, STDERR_FILENO);
	else if (err_type == ERR_PIPE)
		ft_putstr_fd(ERR_PIPE_MSG, STDERR_FILENO);
	else if (err_type == ERR_FORK)
		ft_putstr_fd(ERR_FORK_MSG, STDERR_FILENO);
	else if (err_type == ERR_EXEC)
		ft_putstr_fd(ERR_EXEC_MSG, STDERR_FILENO);
	else if (err_type == ERR_FILE)
		ft_putstr_fd(ERR_FILE_MSG, STDERR_FILENO);
	else if (err_type == ERR_QUO)
		ft_putstr_fd(ERR_QUO_MSG, STDERR_FILENO);
	else if (err_type == ERR_PAR)
		ft_putstr_fd(ERR_PAR_MSG, STDERR_FILENO);
	else if (err_type == ERR_MALLOC_FAIL)
		ft_putstr_fd(ERR_MALLOC_FAIL_MSG, STDERR_FILENO);
}

int	ft_error(t_error_type err_type, t_tools *tools)
{
	(void)tools;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err_type == ERR_SYNTAX)
		ft_putstr_fd(ERR_SYNTAX_MSG, STDERR_FILENO);
	else if (err_type == ERR_TOO_MANY_ARGS)
		ft_putstr_fd(ERR_TOO_MANY_ARGS_MSG, STDERR_FILENO);
	else if (err_type == ERR_NUMERIC_ARG_REQUIRED)
		ft_putstr_fd(ERR_NUMERIC_ARG_REQUIRED_MSG, STDERR_FILENO);
	else if (err_type == ERR_HOME_NOT_SET)
		ft_putstr_fd(ERR_HOME_NOT_SET_MSG, STDERR_FILENO);
	else if (err_type == ERR_OLDPWD_NOT_SET)
		ft_putstr_fd(ERR_OLDPWD_NOT_SET_MSG, STDERR_FILENO);
	else if (err_type == ERR_INVALID_IDENTIFIER)
		ft_putstr_fd(ERR_INVALID_IDENTIFIER_MSG, STDERR_FILENO);
	else if (err_type == ERR_LEX)
		ft_putstr_fd(ERR_LEX_MSG, STDERR_FILENO);
	else
		error_extension(err_type);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_path_error(t_error_type err_type, t_tools *tools, char *path)
{
	char	*temp;
	char	*path_err;

	temp = NULL;
	(void)tools;
	if (path)
		path_err = ft_strjoin(path, ": ");
	else
		path_err = ft_strdup("");
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err_type == ERR_NO_SUCH_FILE)
		temp = ft_strjoin(path_err, ERR_NO_SUCH_FILE_MSG);
	else if (err_type == ERR_PERMISSION_DENIED)
		temp = ft_strjoin(path_err, ERR_PERMISSION_DENIED_MSG);
	else if (err_type == ERR_IS_A_DIRECTORY)
		temp = ft_strjoin(path_err, ERR_IS_A_DIRECTORY_MSG);
	else if (err_type == ERR_CMD_NOT_FOUND)
		temp = ft_strjoin(path_err, ERR_CMD_NOT_FOUND_MSG);
	if (!temp)
		return (ft_error(ERR_MALLOC_FAIL, tools));
	ft_putendl_fd(temp, STDERR_FILENO);
	if (path_err)
		free(path_err);
	free(temp);
	return (EXIT_FAILURE);
}
