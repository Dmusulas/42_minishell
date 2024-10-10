/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:49 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/10 17:58:39 by pmolzer          ###   ########.fr       */
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
	(void)envp; // We don't need to store envp anymore
	tools.debug_mode = true;
	rl_catch_signals = 0;
	init_tools(&tools);
	mini_loop(&tools);
	return (0);
}
