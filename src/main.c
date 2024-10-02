/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:17:00 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
rl_catch_signals:
	if not disabled Readline internal sig handling messes up our sig handler
	BUT leaves memory blocks still accessable....
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_tools	tools;

	(void)argc;
	(void)argv;
	tools.envp_org = envp;
	tools.debug_mode = true;
	rl_catch_signals = 0;
	if (!duplicate_env(&tools))
	{
		ft_putendl_fd("Failed to duplicate environment variables",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (tools.debug_mode)
		print_linkedlist(tools.envp);
	init_tools(&tools);
	mini_loop(&tools);
	return (0);
}
