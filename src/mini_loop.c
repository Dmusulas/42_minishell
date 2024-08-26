/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:19:47 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/22 18:04:52 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "exec.h"
#include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

int		mini_loop(t_tools *tools);

void	clean_tools(t_tools *tools)
{
	if (tools->args != NULL)
		free(tools->args);
	if (tools->lexer_lst != NULL)
		clear_tokens(&tools->lexer_lst);
	if (tools->redir != NULL)
		clear_tokens(&tools->redir);
}

void	init_tools(t_tools *tools)
{
	tools->args = NULL;
	tools->lexer_lst = NULL;
	tools->redir = NULL;
	tools->redir_num = 0;
	tools->pipes = 0;
	init_signals();
}

int	reset_tools(t_tools *tools)
{
	clean_tools(tools);
	init_tools(tools);
	mini_loop(tools);
	return (1);
}

int	prep_exec(t_tools *tools)
{
	(void)tools;
	signal(SIGQUIT, sigquit_handler);
	executor(tools);
	return (EXIT_SUCCESS);
}

/*
save lines if return value is int
*/
int	mini_loop(t_tools *tools)
{
	char	*tmp;

	tools->args = readline("minishell$ ");
	if (tools->args == NULL)
	{
		ft_putendl_fd("minishell$: exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (tools->args == NULL || tools->args[0] == '\0') // Handle empty input
		return (reset_tools(tools));
	add_history(tools->args);
	if (!check_quotes(tools->args))
		return (ft_error(ERR_QUO, tools));
	if (!tokenize_input(tools))
		return (ft_error(ERR_LEX, tools));
	if (tools->lexer_lst)
		print_tokens(tools->lexer_lst);
	prep_exec(tools);
	reset_tools(tools);
	return (1);
}

int	executor(t_tools *tools)
{
	t_exec	*exec;

	if (argc >= 0)
	{
		exec = init_exec(argc);
		set_infile(argv, exec);
		set_outfile(argv[argc - 1], exec);
		exec->cmd_paths = parse_cmds(exec, argv, tools->envp);
		exec->cmd_args = parse_args(exec, argv);
		ft_exec(exec, tools->envp);
		close(exec->in_fd);
		close(exec->out_fd);
		free_exec(exec);
	}
	else
		return (0);
	return (1);
}
