/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:10:57 by pmolzer           #+#    #+#             */
/*   Updated: 2024/11/05 13:24:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_tools *tools)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		free(pwd);
		return (0);
	}
	else
	{
		if (errno == ENOENT)
			return (ft_path_error(ERR_NO_SUCH_FILE, tools, NULL));
		else if (errno == EACCES)
			return (ft_path_error(ERR_PERMISSION_DENIED, tools, NULL));
	}
	return (ft_path_error(ERR_NO_SUCH_FILE, tools, NULL));
}
