/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:22:53 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/14 17:26:55 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --leak-check=full --show-leak-kinds=all ./minishell

// #include "exec.h"
#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"
#include <stdlib.h>

void	init_tools(t_tools *tools)
{
	tools->args = NULL;
	tools->lexer_lst = NULL;
	tools->p_redir = NULL;
	tools->redir_num = 0;
	tools->pipes = 0;
	tools->heredoc = false;
	tools->in_fd = 0;
	tools->out_fd = 0;
	tools->tree = NULL;
	init_signals();
}

// This function should be called only once at the start of the program
void	set_initial_exit_status(t_tools *tools)
{
	tools->last_exit_status = 0;
}

int	reset_tools(t_tools *tools)
{
	if (tools != NULL)
		clean_tools(tools);
	init_tools(tools);
	mini_loop(tools);
	return (0);
}

/*
	handle_input
		quotes/match check, sends error msg if not correct + restart
		tokenize_input (+ chceck if NULL, error msg + restart)
		labels T_ARG / T_CMD
		process token -> assigns values vars related to redir tokens
*/
int	mini_loop(t_tools *tools)
{
	tools->args = readline("minishell$ ");
	if (tools->debug_mode)
		printf("[DEBUG]: received arguments %s\n", tools->args);
	if (tools->args == NULL)
	{
		ft_putendl_fd("minishell$ exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (!tools->args || tools->args[0] == '\0')
		return (reset_tools(tools));
	add_history(tools->args);
	handle_input(tools);
	execute_command(tools->tree, tools);
	printf("[DEBUG] Last exit status preserved: %d\n", tools->last_exit_status);
	reset_tools(tools);
	return (1);
}
