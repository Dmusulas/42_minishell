/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:01:01 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/26 14:47:42 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Main loop + history and signal handling.

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
	tools.envp = envp;
	rl_catch_signals = 0;
	if (tools.envp == NULL)
	{
		ft_putendl_fd("Failed to duplicate environment variables",
			STDERR_FILENO);
		return (EXIT_FAILURE);
		// Exit if environment duplication fails.
	}
	init_tools(&tools);
	mini_loop(&tools);
	return (0);
}
