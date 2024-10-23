/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:11:20 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/23 11:11:32 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;

	current = cmd_node;
	while (current)
	{
		remove_env_var(&tools->envp, current->str);
		current = current->right;
	}
	return (0);
}