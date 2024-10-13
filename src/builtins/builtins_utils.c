/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:07:03 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/12 22:40:04 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strncmp(env_var, var_name,
				var_len) == 0 && env_var[var_len] == '=')
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

void	change_to_absolute_path(char *path)
{
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
}

void	change_to_relative_path(char *path, t_tools *tools)
{
	char	*cwd;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return ;
	}
	full_path = ft_strjoin(cwd, "/");
	full_path = ft_strjoin(full_path, path);
	free(cwd);
	if (tools->debug_mode)
		printf("[DEBUG]: Changing to relative path: %s\n", full_path);
	if (chdir(full_path) == -1)
		printf("cd: %s: No such file or directory\n", path);
	free(full_path);
}
