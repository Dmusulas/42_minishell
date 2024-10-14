/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/12 22:37:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	ft_pwd(t_tools *tools)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		free(pwd);
	}
	else
		perror("pwd");
	if (tools->debug_mode)
	{
		printf("[DEBUG]: ft_pwd() executed\n");
	}
}

void	ft_unset(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;

	current = cmd_node;
	while (current)
	{
		remove_env_var(&tools->envp, current->str);
		current = current->right;
	}
}

void	ft_exit(t_tools *tools)
{
	if (tools->debug_mode)
		printf("[DEBUG]: ft_exit() executed\n");
	exit(0);
}

void	execute_builtin(t_ast *cmd_node, t_tools *tools)
{
	if (ft_strcmp(cmd_node->str, "echo") == 0)
		ft_echo(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "cd") == 0)
	{
		if (cmd_node->right)
			ft_cd(cmd_node->right->str, tools);
		else
			ft_cd(NULL, tools);
	}
	else if (ft_strcmp(cmd_node->str, "pwd") == 0)
		ft_pwd(tools);
	else if (ft_strcmp(cmd_node->str, "export") == 0)
	{
		ft_export(cmd_node->right, tools);
	}
	else if (ft_strcmp(cmd_node->str, "unset") == 0)
		ft_unset(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "env") == 0)
		ft_env(tools);
	else if (ft_strcmp(cmd_node->str, "exit") == 0)
		ft_exit(tools);
}
