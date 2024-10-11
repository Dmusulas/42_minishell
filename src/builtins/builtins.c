/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/11 16:32:06 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	ft_env(t_tools *tools)
{
	t_list	*current;
	char	*env_var;

	current = tools->envp;
	while (current)
	{
		env_var = (char *)current->content;
		write(STDOUT_FILENO, env_var, ft_strlen(env_var));
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
	if (tools->debug_mode)
	{
		printf("[DEBUG]: ft_env() executed\n");
	}
}

static void	remove_env_var(t_list **envp, const char *var_name)
{
	t_list	*prev;
	t_list	*current;
	char	*env_var;
	char	*equals_pos;

	prev = NULL;
	current = *envp;
	while (current)
	{
		env_var = (char *)current->content;
		equals_pos = ft_strchr(env_var, '=');
		if (equals_pos && ft_strncmp(env_var, var_name, equals_pos
				- env_var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static void	unset_single_var(t_ast *arg_node, t_list **envp)
{
	if (arg_node && arg_node->str)
		remove_env_var(envp, arg_node->str);
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
	char	*expanded_str;

	current = cmd_node->right;
	n_line = 1;
	if (current && ft_strcmp(current->str, "-n") == 0)
	{
		n_line = 0;
		current = current->right;
	}
	while (current)
	{
		printf("[DEBUG] Echo: Expanding '%s'\n", current->str);
		expanded_str = expand_var(current->str, tools);
		printf("[DEBUG] Echo: Expanded to '%s'\n", expanded_str);
		ft_putstr_fd(expanded_str, STDOUT_FILENO);
		free(expanded_str);
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

	current = cmd_node;
	if (!current)
	{
		ft_env(tools);
		return ;
	}
	while (current)
	{
		arg = current->str;
		if (tools->debug_mode)
			printf("[DEBUG] Exporting argument: %s\n", arg);
		if (ft_strchr(arg, '='))
		{
			if (tools->debug_mode)
				printf("[DEBUG] Exporting: %s\n", arg);
			int result = update_or_add_envp(&tools->envp, arg);
			if (tools->debug_mode)
				printf("[DEBUG] update_or_add_envp result: %d\n", result);
		}
		else
		{
			if (tools->debug_mode)
				printf("[DEBUG] Marking as exportable: %s\n", arg);
			// Here you might want to mark the variable as exportable without setting a value
		}
		current = current->right;
	}
	if (tools->debug_mode)
	{
		printf("[DEBUG]: ft_export() executed\n");
		printf("[DEBUG]: Current environment variables:\n");
		print_linkedlist(tools->envp);
	}
}

void	ft_unset(t_ast *cmd_node, t_tools *tools)
{
	t_ast	*current;

	current = cmd_node->right;
	while (current)
	{
		unset_single_var(current, &tools->envp);
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
		ft_export(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "unset") == 0)
		ft_unset(cmd_node->right, tools);
	else if (ft_strcmp(cmd_node->str, "env") == 0)
		ft_env(tools);
	else if (ft_strcmp(cmd_node->str, "exit") == 0)
		ft_exit(tools);
}
