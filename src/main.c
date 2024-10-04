/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/03 22:36:08 by pmolzer          ###   ########.fr       */
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
	init_tools(&tools);
	mini_loop(&tools);
	return (0);
}
