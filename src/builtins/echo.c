/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:33:09 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/14 17:12:43 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_argument(t_ast *current, t_tools *tools)
{
	char	*expanded_str;

	if (ft_strcmp(current->str, "$?") == 0)
		ft_putnbr_fd(tools->last_exit_status, STDOUT_FILENO);
	else
	{
		expanded_str = expand_var(current->str, tools);
		ft_putstr_fd(expanded_str, STDOUT_FILENO);
		free(expanded_str);
	}
}

int	ft_echo(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;
	int		n_line;

	current = cmd_node->right;
	n_line = 1;
	if (current && ft_strcmp(current->str, "-n") == 0)
	{
		n_line = 0;
		current = current->right;
	}
	while (current)
	{
		print_argument(current, tools);
		if (current->right)
			ft_putchar_fd(' ', STDOUT_FILENO);
		current = current->right;
	}
	if (n_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (tools->debug_mode)
		printf("[DEBUG]: ft_echo() executed\n");
	return (0);
}
