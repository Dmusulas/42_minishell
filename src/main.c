/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/17 16:47:43 by pmolzer          ###   ########.fr       */
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
	set_initial_exit_status(&tools);
	mini_loop(&tools);
	if (tools.envp != NULL)
		delete_duplicated_envp(&tools);
	return (0);
}

// create a new header file for error handling
// implement relative path for minishell: like ./minishell or .././minishell or smth like that
//			--> orient yourself to bash
// check what this rl_catch_signals and rl_event_hook do --> connected to the event function in signals
// double check if the export function now works