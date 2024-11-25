/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:40:50 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/25 16:03:15 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_validation(char *arg, t_tools *tools)
{
	int		i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_error(ERR_INVALID_IDENTIFIER, tools);
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_error(ERR_INVALID_IDENTIFIER, tools);
			return (0);
		}
		i++;
	}
	return (1);
}

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
		if (!export_validation(arg, tools))
			success = 1;
		else if (ft_strchr(arg, '='))
		{
			if (update_or_add_envp(&tools->envp, arg) != 0)
				success = 1;
			ft_lstsort(&tools->envp, cmp_envp);
			return (success);
		}
		current = current->right;
	}
	return (success);
}
