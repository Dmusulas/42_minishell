/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:00 by pmolzer           #+#    #+#             */
/*   Updated: 2024/12/01 16:27:09 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

bool	is_special_env_var(const char *str)
{
	return (ft_strcmp(str, "$") == 0 || ft_strcmp(str, "$?") == 0);
}

void	handle_directory_error(char *env_value, t_tools *tools)
{
	ft_putstr_fd(env_value, 2);
	ft_path_error(ERR_IS_A_DIRECTORY, tools, env_value);
	tools->last_exit_status = 126;
	exit(126);
}

void	handle_empty_env(t_ast *node, t_tools *tools)
{
	if (!node->right)
	{
		tools->last_exit_status = 0;
		exit(0);
	}
}
