/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:34:42 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/12 22:40:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *path, t_tools *tools)
{
	if (!path)
	{
		write(STDERR_FILENO, "cd: expected argument\n", 22);
		return ;
	}
	if (path[0] == '/')
		change_to_absolute_path(path);
	else
		change_to_relative_path(path, tools);
	if (tools->debug_mode)
		printf("[DEBUG]: ft_cd() executed with path: %s\n", path);
}
