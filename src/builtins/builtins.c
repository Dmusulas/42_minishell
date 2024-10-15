/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/14 16:57:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

int	ft_pwd(t_tools *tools)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		free(pwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
	if (tools->debug_mode)
		printf("[DEBUG]: ft_pwd() executed\n");
}

int	ft_unset(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;

	current = cmd_node;
	while (current)
	{
		remove_env_var(&tools->envp, current->str);
		current = current->right;
	}
	return (0);
}

void	ft_exit(t_tools *tools)
{
	if (tools->debug_mode)
		printf("[DEBUG]: ft_exit() executed\n");
	exit(0);
}

void	execute_builtin(t_ast *cmd_node, t_tools *tools)
{
	int		status_result;

	status_result = 0;
	if (ft_strcmp(cmd_node->str, "echo") == 0)
		status_result = ft_echo(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "cd") == 0)
	{
		if (cmd_node->right)
			status_result = ft_cd(cmd_node->right->str, tools);
		else
			status_result = ft_cd(NULL, tools);
	}
	else if (ft_strcmp(cmd_node->str, "pwd") == 0)
		status_result = ft_pwd(tools);
	else if (ft_strcmp(cmd_node->str, "export") == 0)
	{
		status_result = ft_export(cmd_node->right, tools);
	}
	else if (ft_strcmp(cmd_node->str, "unset") == 0)
		status_result = ft_unset(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "env") == 0)
		status_result = ft_env(tools);
	else if (ft_strcmp(cmd_node->str, "exit") == 0)
		ft_exit(tools);
	tools->last_exit_status = status_result;
}
