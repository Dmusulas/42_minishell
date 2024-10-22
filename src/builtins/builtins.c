/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/22 17:12:21 by pmolzer          ###   ########.fr       */
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
		return (ft_error(ERR_NO_SUCH_FILE, tools));
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

int	ft_exit(t_ast *cmd_node, t_tools *tools)
{
	long long	exit_code;
	char		*arg;

	exit_code = 0;
	if (tools->debug_mode)
		printf("[DEBUG]: ft_exit() executed\n");
	printf("exit\n");
	if (cmd_node->right)
	{
		arg = cmd_node->right->str;
		if (ft_is_not_integer(arg))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO); // add here ft_error
			exit(2);
		}
		exit_code = ft_atoi(arg);
		if (cmd_node->right->right)
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO); // add here ft_error
			return (1);
		}
	}
	clean_tools(tools);
	exit((unsigned char)exit_code);
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
		status_result = ft_exit(cmd_node, tools);
	tools->last_exit_status = status_result;
}
