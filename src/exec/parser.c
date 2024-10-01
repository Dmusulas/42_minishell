/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:48 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:34:48 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

/**
 * This function finds a path of provided command from ENV PATH variable
 *
 * @param envp enviroment string
 * @return pointer to the PATH variable
 */
static char	*find_path(char **envp)
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
 * Finds an executable cmd from path if not found use calloc to
 * allocate memory with NULLs so they can be freed propery even if cmd
 * does not exists.
 *
 * @param paths takes paths retrieved from env variable
 * @param cmd which cmd to find
 * @return a path to cmd in a system
 */
static char	*find_cmd(char *paths, char *cmd, t_exec *exec)
{
	char	*full_cmd;
	char	**paths_split;
	int		i;

	paths_split = ft_split(paths, ':');
	if (!paths_split)
		msg_error(ERR_MALLOC, exec);
	i = 0;
	while (paths_split[i])
	{
		full_cmd = join_paths(paths_split[i], cmd);
		if (!full_cmd)
			msg_error(ERR_MALLOC, exec);
		if (!access(full_cmd, X_OK))
		{
			free_2darray(paths_split);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_2darray(paths_split);
	ft_printf("%s: command not found\n", cmd);
	return (ft_calloc(1, 1));
}

/**
 * This functions parses the argv to get correct path to executables
 *
 * @param argc argument count from main
 * @param argv argument array from main
 * @param envp environment variable array from the main
 * @return an array with paths to all executbales
 */
char	**parse_cmds(t_exec *exec, char **argv, char **envp)
{
	char	**cmds;
	char	*cmd;
	char	*paths;
	int		i;
	char	**temp;

	i = 0;
	paths = find_path(envp);
	cmds = malloc((exec->cmd_count + 1) * sizeof(char *));
	if (!cmds)
		msg_error(ERR_MALLOC, exec);
	while (i < exec->cmd_count)
	{
		temp = ft_split(argv[i + exec->cmd_start_position], ' ');
		cmd = find_cmd(paths, temp[0], exec);
		if (cmd)
			cmds[i] = cmd;
		else
			cmds[i] = NULL;
		free_2darray(temp);
		i++;
	}
	cmds[i] = NULL;
	free(paths);
	return (cmds);
}

/**
 * This functions parses the argv to get commands and their arguments
 *
 * @param argc argument count from main
 * @param argv argument array from main
 * @return a 2D array with commands and their args
 */
char	***parse_args(t_exec *exec, char **argv)
{
	char	***args;
	int		i;

	i = 0;
	args = malloc((exec->cmd_count + 1) * sizeof(char **));
	if (!args)
		msg_error(ERR_MALLOC, exec);
	while (i < exec->cmd_count)
	{
		args[i] = ft_split(argv[i + exec->cmd_start_position], ' ');
		i++;
	}
	args[i] = NULL;
	return (args);
}
