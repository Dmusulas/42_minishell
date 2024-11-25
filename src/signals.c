/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:22 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/25 14:51:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sigint_handler_active(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	sigint_handler_inactive(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	(void)signal;
}

void	sigquit_handler_inactive(int signal)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(signal, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	set_active_signals(void)
{
	struct sigaction sa;
	
	sa.sa_handler = sigint_handler_active;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_inactive_signals(void)
{
	struct sigaction sa;
	
	sa.sa_handler = sigint_handler_inactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = sigquit_handler_inactive;
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_signals(void)
{
	set_active_signals();
}
