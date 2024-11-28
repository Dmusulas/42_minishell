/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:22 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/25 15:00:48 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles signals in interactive mode, specifically SIGINT.
 * - Prints a newline
 * - Clears the current line
 * - Redisplays the prompt.
 *
 * @param signal The signal received.
 */
static void	handle_active_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * Handles signals in non-interactive mode.
 * - Prints a newline for SIGINT.
 * - Prints a "Quit" message for SIGQUIT along with the signal number.
 *
 * @param signal The signal received.
 */
static void	handle_inactive_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(signal, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

/**
 * Sets up signal handling by defining the handler for SIGINT and
 * SIGQUIT signals using the provided handler function.
 *
 * @param handler The function to handle the signal.
 */
static void	setup_signals(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * Configures signal handling for interactive mode by setting the
 * active signal handler.
 */
void	set_active_signals(void)
{
	setup_signals(handle_active_signal);
}

/**
 * Configures signal handling for non-interactive mode by setting
 * the inactive signal handler.
 */
void	set_inactive_signals(void)
{
	setup_signals(handle_inactive_signal);
}
