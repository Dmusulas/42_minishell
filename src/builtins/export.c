/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:40:50 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 14:19:22 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_validation(char *arg, t_tools *tools)
{
	int i;

	if (tools->debug_mode)
		printf("[DEBUG] Validating: %s\n", arg);

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		if (tools->debug_mode)
			printf("[DEBUG] Invalid first character\n");
		ft_error(ERR_INVALID_IDENTIFIER, tools);
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (tools->debug_mode)
				printf("[DEBUG] Invalid character: %c at position %d\n", arg[i], i);
			ft_error(ERR_INVALID_IDENTIFIER, tools);
			return (0);
		}
		i++;
	}
	if (tools->debug_mode)
		printf("[DEBUG] Validation passed\n");
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
		if (tools->debug_mode)
			printf("[DEBUG] Processing argument: %s\n", arg);
		
		if (!export_validation(arg, tools))
		{
			if (tools->debug_mode)
				printf("[DEBUG] Validation failed\n");
			success = 1;
		}
		else if (ft_strchr(arg, '='))
		{
			if (tools->debug_mode)
				printf("[DEBUG] Updating or adding to envp\n");
			if (update_or_add_envp(&tools->envp, arg) != 0)
				success = 1;
		}
		else
		{
			if (tools->debug_mode)
				printf("[DEBUG] Printing linked list\n");
			print_linkedlist(tools->envp);
		}
		current = current->right;
	}
	return (success);
}
