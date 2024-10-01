/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:19:47 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:19:47 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	mini_loop(t_tools *tools);
int		executor(t_tools *tools, int argc, char *argv[]);

void	reset_tools(t_tools *tools)
{
	if (tools->args != NULL)
		free(tools->args);
	mini_loop(tools);
}

void	mini_loop(t_tools *tools)
{
	char	**argv;
	int		argc;

	argc = 0;
	tools->debug_mode = true;
	tools->args = readline("minishell$ ");
	if (tools->debug_mode)
		printf("[DEBUG]: received arguments %s\n", tools->args);
	if (tools->args == NULL)
	{
		ft_putendl_fd("minishell$: exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (tools->args[0] != '\0')
	{
		add_history(tools->args);
		argv = ft_split(tools->args, ' ');
		while (argv[argc] != NULL)
			argc++;
		executor(tools, argc, argv);
	}
	reset_tools(tools);
}

int	executor(t_tools *tools, int argc, char *argv[])
{
	t_exec	*exec;

	if (tools->debug_mode)
		printf("[DEBUG]: argc=%i argv[0]='%s'\n", argc, argv[0]);
	if (argc >= 1)
	{
		exec = init_exec(argc);
		// set_infile(argv, exec);
		// set_outfile(argv[argc - 1], exec);
		// exec->cmd_paths = parse_cmds(exec, argv, tools->envp);
		// exec->cmd_args = parse_args(exec, argv);
		if (tools->debug_mode)
			printf("[DEBUG]: cmd_args[0]=%s \n", exec->cmd_args[0]);
		// ft_exec(exec, tools->envp);
		// close(exec->in_fd);
		// close(exec->out_fd);
		free_exec(exec);
	}
	else
		return (0);
	return (1);
}
