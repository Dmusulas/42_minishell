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

/**
 * Updates the PWD and OLDPWD environment variables after a directory change.
 */
int	cd_update_env_paths(t_tools *tools)
{
	char	*pwd;
	char	*oldpwd_env;
	char	*newpwd;

	pwd = get_env_value("PWD", tools);
	if (pwd)
	{
		oldpwd_env = ft_strjoin("OLDPWD=", pwd);
		if (oldpwd_env)
		{
			update_or_add_envp(&tools->envp, oldpwd_env);
			free(oldpwd_env);
		}
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_or_add_envp(&tools->envp, ft_strjoin("PWD=", newpwd));
		free(newpwd);
	}
	else
	{
		update_or_add_envp(&tools->envp, ft_strjoin("PWD=", pwd));
	}
	return (0);
}

/**
 * Changes the current directory, handling HOME, OLDPWD, and error conditions.
 *
 * @param path: The target directory path to change to.
 * @param tools: The tools struct containing environment variables.
 * @return: 0 on success, or an error code on failure.
 */
int	ft_cd(char *path, t_tools *tools)
{
	char	*home;
	char	*oldpwd;

	home = get_env_value("HOME", tools);
	oldpwd = get_env_value("OLDPWD", tools);
	if (!path)
	{
		if (!home)
			return (ft_error(ERR_HOME_NOT_SET, tools));
		path = home;
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (!oldpwd)
			return (ft_error(ERR_OLDPWD_NOT_SET, tools));
		path = oldpwd;
	}
	if (chdir(path) != 0)
	{
		if (errno == ENOENT)
			return (ft_path_error(ERR_NO_SUCH_FILE, tools, path));
		if (errno == EACCES)
			return (ft_path_error(ERR_PERMISSION_DENIED, tools, path));
	}
	return (cd_update_env_paths(tools));
}
