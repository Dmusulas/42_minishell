/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/29 16:16:24 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
rl_catch_signals:
	if not disabled Readline internal sig handling messes up our sig handler
	BUT leaves memory blocks still accessible....
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
		return (ft_error(ERR_MALLOC, &tools));
	init_tools(&tools);
	set_initial_exit_status(&tools);
	mini_loop(&tools);
	if (tools.envp != NULL)
		delete_duplicated_envp(&tools);
	return (0);
}
