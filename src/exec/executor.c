/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/15 11:18:37 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer_parser.h"
#include "libft.h"
#include "minishell.h"

static void	handle_redirect(t_ast *node, t_tools *tools)
{
	if (node->token == T_REDIR_IN || node->token == T_HEREDOC)
		set_infile(node);
	else if (node->token == T_REDIR_OUT)
		set_outfile(node, false);
	else if (node->token == T_APPEND)
		set_outfile(node, true);
	execute_command(node->left, tools);
}

static void	handle_command(t_ast *node, t_tools *tools)
{
	pid_t	pid;

	if (node->b_cmd)
		execute_builtin(node, tools);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			exec_cmd(node, list_to_array(tools->envp));
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}

void	exec_cmd(t_ast *node, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	char	*path_var;

	path_var = find_path(envp);
	if (!path_var)
	{
		perror("PATH variable not found");
		exit(EXIT_FAILURE);
	}
	cmd_path = find_cmd(path_var, node->str);
	free(path_var);
	if (!cmd_path || !*cmd_path)
	{
		ft_printf("%s: command not found\n", node->str);
		free(cmd_path);
	}
	cmd_args = parse_cmd_args(cmd_path, node);
	if (execve(cmd_path, cmd_args, envp) == -1)
		perror("Execve failed");
}

void	execute_command(t_ast *node, t_tools *tools)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!node)
		return ;
	save_stdin_stdout(&saved_stdin, &saved_stdout);
	if (node->token == T_PIPE)
		handle_pipes(node, tools);
	else if (token_check(node->token))
		handle_redirect(node, tools);
	else if (node->token == T_CMD)
		handle_command(node, tools);
	restore_stdin_stdout(saved_stdin, saved_stdout);
}
