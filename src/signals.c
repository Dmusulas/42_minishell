/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:22 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/21 17:23:37 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
handles Ctrl+C
write("\n") to go to newline
rl_replace_line: replaces the current input line with a new string.
rl_on_new_line: informs Readline that the cursor is at a new line
rl_redisplay: tells Readline to update/redraw the current display.
(void)signal: suppress unused parameter warning
*/
void	sigint_handler(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

/*
call "signal(SIGQUIT, sigquit_handler);" before command execution
when a command is being executed, if SIGQUIT -> handle accordingly

handles Ctrl+'\'
prints: Quit: , signal number and '\n'
*/
void	sigquit_handler(int signal)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(signal, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

/*
Set the event hook function to be called periodically by Readline.
Set the SIGINT signal handler to sigint_handler.
Ignore the SIGQUIT signal when not in cmd execution.

*/
void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
