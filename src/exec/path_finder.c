/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:41:31 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/10 17:41:31 by dmusulas         ###   ########.fr       */
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
 * @return The full path to the executable command, or a NULL pointer
 * if the command is not found.
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
		if (!full_cmd)
		{
			free_2darray(paths_split);
			return (NULL);
		}
		if (!access(full_cmd, X_OK))
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
