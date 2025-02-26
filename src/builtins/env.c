/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:37:06 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/21 14:33:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_tools *tools)
{
	t_list	*current;
	char	*env_var;

	current = tools->envp;
	while (current)
	{
		env_var = (char *)current->content;
		write(STDOUT_FILENO, env_var, ft_strlen(env_var));
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
	if (tools->debug_mode)
	{
		printf("[DEBUG]: ft_env() executed\n");
	}
	return (0);
}
