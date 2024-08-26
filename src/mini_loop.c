/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:19:47 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/26 12:50:33 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// valgrind --leak-check=full --show-leak-kinds=all ./minishell

// #include "exec.h"
#include "lexer_parser.h"
#include "minishell.h"

int	mini_loop(t_tools *tools);
// int		executor(t_tools *tools, int argc, char *argv[]);

void	init_tools(t_tools *tools)
{
	printf("enter init tools\n");
	tools->args = NULL;
	tools->lexer_lst = NULL;
	tools->p_redir = NULL;
	tools->redir_num = 0;
	tools->pipes = 0;
	tools->heredoc = false;
	tools->in_fd = 0;
	tools->out_fd = 0;;
	// tools->loop_reset = false;
	init_signals();
}

int	reset_tools(t_tools *tools)
{
	printf("enter reset tools\n");
	if (tools != NULL)
		clean_tools(tools);
	init_tools(tools);
	// tools->loop_reset = true;
	mini_loop(tools);
	return(1);
}

static void	exit_signal(void)
{
	ft_putendl_fd("minishell$: exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

/*
	mini loop + reset need to be optimized.
	when testing it causes an error with the first call with token but then not anymore...
	need to test with more debug statements to see whats happening.
*/
int	mini_loop(t_tools *tools)
{
	char	*tmp;

	tools->args = readline("minishell$ ");
	if (tools->args == NULL)
		exit_signal();
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (!tools->args || tools->args[0] == '\0')
		return (reset_tools(tools));
	add_history(tools->args);
	if (!check_quotes(tools->args))
		return (ft_error(ERR_QUO, tools));
	handle_input(tools);
	if (tools->lexer_lst)
		print_tokens(tools->lexer_lst);
	reset_tools(tools);
	return (1);
}

// int prep_exec(t_tools *tools)
// {
// 	signal(SIGQUIT, sigquit_handler);          // Set up handler for SIGQUIT signal
// 	// in command/exec flag on
// 	if no pipes
//	check for redir cmd or buildtin
// 	else
// 	{
// 		// handle pid alloc space for pipe count
// 		// error handle if alloc fail
// 		executor(tools);                     // Execute commands with pipes
// 	}
// 	//reset flag
// 	return (EXIT_SUCCESS);                   // Return success
// }


// int	executor(t_tools *tools, int argc, char *argv[])
// {
// 	t_exec	*exec;

// 	if (argc >= 0)
// 	{
// 		exec = init_exec(argc);
// 		set_infile(argv, exec);
// 		set_outfile(argv[argc - 1], exec);
// 		exec->cmd_paths = parse_cmds(exec, argv, tools->envp);
// 		exec->cmd_args = parse_args(exec, argv);
// 		ft_exec(exec, tools->envp);
// 		close(exec->in_fd);
// 		close(exec->out_fd);
// 		free_exec(exec);
// 	}
// 	else
// 		return (0);
// 	return (1);
// }
