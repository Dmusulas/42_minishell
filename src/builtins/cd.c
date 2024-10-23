/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:34:42 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/23 10:49:35 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path, t_tools *tools)
{
	char	*home;
	char	*oldpwd;

	if (!path)
	{
		home = get_env_value("HOME", tools);
		if (!home)
			return (ft_error(ERR_HOME_NOT_SET, tools));
		return (change_to_absolute_path(home, tools));
	}
	if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = get_env_value("OLDPWD", tools);
		if (!oldpwd)
			return (ft_error(ERR_OLDPWD_NOT_SET, tools));
		return (change_to_absolute_path(oldpwd, tools));
	}
	if (path[0] == '/')
		return (change_to_absolute_path(path, tools));
	else
		return (change_to_relative_path(path, tools));
}
