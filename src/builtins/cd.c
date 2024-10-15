/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:34:42 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/15 11:19:30 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path, t_tools *tools)
{
	if (!path)
	{
		write(STDERR_FILENO, "cd: expected argument\n", 22);
		return (1);
	}
	if (path[0] == '/')
		return (change_to_absolute_path(path));
	else
		return (change_to_relative_path(path, tools));
}
