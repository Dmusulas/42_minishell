/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:40:50 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/17 16:29:25 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_valdidation(char *arg, t_tools *tools)
{
	int	i;

	i = 0;
	if (arg[i] == '_' || (arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z'))
	{
		i++;
		while (arg[i] && arg[i] != '=')
		{
			if (arg[i] == ' ')
			{
				if (tools->debug_mode)
					printf("Error: export: `%s': not a valid identifier\n", arg);
				return (1);
			}
			
			if (!(arg[i] >= 'a' && arg[i] <= 'z') &&
				!(arg[i] >= 'A' && arg[i] <= 'Z') &&
				!(arg[i] >= '0' && arg[i] <= '9') &&
				arg[i] != '_')
			{
				if(tools->debug_mode)
					printf("Error: export: `%s': not a valid identifier\n", arg);
				return (1);
			}
			i++;
		}
		if(tools->debug_mode)
			printf("export: `%s': valid identifier\n", arg);
	}
	else
	{
		if (tools->debug_mode)
			printf("Error: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
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
		if (ft_strchr(arg, '='))
		{
			if(export_valdidation(arg, tools) == 0)
			{
				if (update_or_add_envp(&tools->envp, arg) != 0)
					success = 1;
			}
		}
		else
		{
        	write(STDERR_FILENO, "export: `", 9);
        	write(STDERR_FILENO, arg, ft_strlen(arg));
        	write(STDERR_FILENO, "': not an assignment\n", 20);
        	success = 1;
		}
		current = current->right;
	}
	return (success);
}