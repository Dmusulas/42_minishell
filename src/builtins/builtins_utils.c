/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:07:03 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/22 17:12:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_not_integer(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	remove_env_var(t_list **envp, const char *var_name)
{
	t_list	*prev;
	t_list	*current;
	char	*env_var;
	size_t	var_len;

	prev = NULL;
	current = *envp;
	var_len = ft_strlen(var_name);
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, var_name, var_len) == 0
			&& env_var[var_len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	change_to_absolute_path(char *path, t_tools *tools)
{
	if (chdir(path) == -1)
		return (ft_path_error(ERR_NO_SUCH_FILE, tools, path));
	cd_update_env_paths(tools);
	return (0);
}

int	change_to_relative_path(char *path, t_tools *tools)
{
	char	*cwd;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_path_error(ERR_NO_SUCH_FILE, tools, path));
	full_path = ft_strjoin(cwd, "/");
	full_path = ft_strjoin(full_path, path);
	free(cwd);
	if (tools->debug_mode)
		printf("[DEBUG]: Changing to relative path: %s\n", full_path);
	if (chdir(full_path) == -1)
	{
		ft_path_error(ERR_NO_SUCH_FILE, tools, path);
		free(full_path);
		return (1);
	}
	free(full_path);
	cd_update_env_paths(tools);
	return (0);
}
