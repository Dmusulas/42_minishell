/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/10 18:11:20 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	ft_env(t_tools *tools)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	if (tools->debug_mode)
	{
		printf("[DEBUG]: ft_env() executed\n");
	}
}

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

void	ft_cd(char *path, t_tools *tools)
{
	char	*cwd;
	char	*full_path;

	if (!path)
	{
		printf("cd: expected argument\n");
		return ;
	}
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
			printf("cd: %s: No such file or directory\n", path);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("cd");
			return ;
		}
		full_path = ft_strjoin(cwd, "/");
		full_path = ft_strjoin(full_path, path);
		free(cwd);
		if (chdir(full_path) == -1)
			printf("cd: %s: No such file or directory\n", path);
		free(full_path);
	}
	if (tools->debug_mode)
		printf("[DEBUG]: ft_cd() executed with path: %s\n", path);
}

void	ft_echo(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;
	int		n_line;

	current = cmd_node->right;
	n_line = 1;
	if (current && ft_strcmp(current->str, "-n") == 0)
	{
		n_line = 0;
		current = current->right;
	}
	while (current)
	{
		ft_putstr_fd(current->str, STDOUT_FILENO);
		if (current->right)
			ft_putchar_fd(' ', STDOUT_FILENO);
		current = current->right;
	}
	if (n_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (tools->debug_mode)
		printf("[DEBUG]: ft_echo() executed\n");
}

void	ft_export(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;
	char	*arg;
	char	*equals_pos;

	current = cmd_node->right;
	if (!current)
	{
		// If no arguments, print the sorted environment
		// TODO: Implement a function to print sorted environment
		printf("[DEBUG]: ft_export called with no arguments\n");
		return ;
	}
	while (current)
	{
		arg = current->str;
		equals_pos = ft_strchr(arg, '=');
		if (equals_pos)
		{
			*equals_pos = '\0';// Temporarily split the string
			if (setenv(arg, equals_pos + 1, 1) == 0)
			{
				if (tools->debug_mode)
					printf("[DEBUG]: Successfully exported %s=%s\n",
						arg, equals_pos + 1);
			}
			else
			{
				fprintf(stderr, "Failed to export %s\n", arg);
			}
			*equals_pos = '=';// Restore the string
		}
		else
		{
			// Just mark as exportable (in bash, this would set an empty value)
			if (setenv(arg, "", 1) == 0)
			{
				if (tools->debug_mode)
					printf("[DEBUG]: Successfully marked %s as exportable\n",
						arg);
			}
			else
			{
				fprintf(stderr, "Failed to mark %s as exportable\n", arg);
			}
		}
		current = current->right;
	}
	if (tools->debug_mode)
		printf("[DEBUG]: ft_export() executed\n");
}

void	ft_unset(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;

	current = cmd_node->right;
	while (current)
	{
		if (current->str)
		{
			if (unsetenv(current->str) == 0)
			{
				if (tools->debug_mode)
					printf("[DEBUG]: Successfully unset %s\n", current->str);
			}
			else
			{
				write(STDERR_FILENO, "Failed to unset", 15);
				write(STDERR_FILENO, current->str, ft_strlen(current->str));
				write(STDERR_FILENO, "\n", 1);
			}
		}
		current = current->right;
	}
	if (tools->debug_mode)
		printf("[DEBUG]: ft_unset() executed\n");
}

void	ft_exit(t_tools *tools)
{
	if (tools->debug_mode)
		printf("[DEBUG]: ft_exit() executed\n");
	exit(0);
}

static void	execute_builtin(t_ast *cmd_node, t_tools *tools)
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
		ft_export(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "unset") == 0)
		ft_unset(cmd_node, tools);
	else if (ft_strcmp(cmd_node->str, "env") == 0)
		ft_env(tools);
	else if (ft_strcmp(cmd_node->str, "exit") == 0)
		ft_exit(tools);
}

void	execute_command(t_ast *node, t_tools *tools)
{
	if (node->token == T_PIPE)
	{
		// Handle pipe execution
		execute_command(node->left, tools);
		execute_command(node->right, tools);
	}
	else if (node->token == T_CMD)
	{
		printf("[DEBUG]: executing command\n");
		if (node->b_cmd)
			execute_builtin(node, tools);
		else
		{
			// Execute external command
		}
	}
	// Handle other token types as needed
}

void	execute_ast(t_tools *tools)
{
	if (tools->tree)
		execute_command(tools->tree, tools);
}
