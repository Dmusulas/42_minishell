/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:40:50 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:03 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;
	char	*arg;
	int		success;

	success = 0;
	current = cmd_node;
	if (!current)
	{
		ft_env(tools);
		return (success);
	}
	while (current)
	{
		arg = current->str;
		if (ft_strchr(arg, '='))
		{
			if (update_or_add_envp(&tools->envp, arg) != 0)
				success = 1;
		}
		else
			print_linkedlist(tools->envp);
		current = current->right;
	}
	return (success);
}
