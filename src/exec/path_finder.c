/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:41:31 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 15:10:27 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * This function finds the PATH variable from the environment variables.
 *
 * @param envp The array of environment variables.
 * @return A newly allocated string containing the PATH variable's value,
 * or NULL if not found.
 */
char	*find_path(char **envp)
{
	char	*prefix;
	int		prefix_len;

	prefix = "PATH=";
	prefix_len = ft_strlen(prefix);
	while (*envp)
	{
		if (ft_strncmp(prefix, *envp, prefix_len) == 0)
		{
			return (ft_substr(*envp, prefix_len, ft_strlen(*envp)
					- prefix_len));
		}
		envp++;
	}
	return (NULL);
}

/**
 * Joins a given path and command into a single string representing
 * the full command path.
 *
 * @param path The base path to the command.
 * @param cmd The command to be appended to the path.
 * @return A newly allocated string containing the full command path.
 */
static char	*join_paths(char *path, char *cmd)
{
	char	*temp;
	char	*full_cmd;

	temp = ft_strjoin(path, "/");
	full_cmd = ft_strjoin(temp, cmd);
	free(temp);
	return (full_cmd);
}

/**
 * Finds an executable command in the provided paths.
 *
 * @param paths The colon-separated PATH string from the environment.
 * @param cmd The command to find.
 * @return The full path to the executable command, or NULL if not found.
 */
char	*find_cmd(char *paths, char *cmd)
{
	char	*full_cmd;
	char	**paths_split;
	int		i;

	paths_split = ft_split(paths, ':');
	if (!paths_split)
		return (NULL);
	i = 0;
	while (paths_split[i])
	{
		full_cmd = join_paths(paths_split[i], cmd);
		if (full_cmd && !access(full_cmd, X_OK))
		{
			free_2darray(paths_split);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_2darray(paths_split);
	return (NULL);
}

/**
 * Checks if the given command is an absolute or relative path.
 * An absolute path starts with a `/`, and a relative path starts with `./`,
	`../`, or similar.
 *
 * @param cmd The command string to check.
 * @return 1 if the command is an absolute or relative path, 0 otherwise.
 */
int	is_absolute_or_relative_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (!(ft_strncmp("/", cmd, 1)))
		return (1);
	if (!ft_strncmp("./", cmd, 2) || !ft_strncmp("../", cmd, 3))
		return (1);
	return (0);
}

/**
 * Resolves a relative path to an absolute paths
 * using the current working directory.
 *
 * @param rel_path The relative path to resolve.
 * @return The full absolute path, or NULL if an error occurs.
 */
char	*resolve_relative_path(char *rel_path, t_tools *tools)
{
	char	*cwd;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_error(ERR_EXECVE_FAIL, tools);
		return (NULL);
	}
	full_path = join_paths(cwd, rel_path);
	free(cwd);
	return (full_path);
}
