/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:26:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/03 22:35:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void ft_pwd(t_tools *tools)
{ // remove tools->debug_mode
    char *pwd = getcwd(NULL, 0);
    if (pwd)
    {
        write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
        free(pwd);
    }
    else
    {
        perror("pwd");
    }
    if (tools->debug_mode)
    {
        printf("[DEBUG]: ft_pwd() executed\n");
    }
}

void ft_cd(char *path, t_tools *tools)
{ // remove tools->debug_mode
    if (path)
    {
        if (path[0] == '/')
        {
            // Path is absolute, directly change directory
            if (chdir(path) == -1)
            {
                perror("cd");
            }
        }
        else
        {
            // Path is relative, prepend the current working directory
            char *cwd = getcwd(NULL, 0);
            char *full_path = ft_strjoin(cwd, path);
            free(cwd);
            if (chdir(full_path) == -1)
            {
                perror("cd");
            }
            free(full_path);
        }
    }
    else
    {
        printf("cd: expected argument\n");
    }
    if (tools->debug_mode)
    {
        printf("[DEBUG]: ft_cd() executed with path: %s\n", path);
    }
}

void ft_echo(char **args, t_tools *tools)
{ // remove tools->debug_mode
    int i;
	int n_line;

	i = 1;
	n_line = 1; // echo adds by default a new line
    // Check for -n option
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0; // Do not print newline
		i++;
	}
	// add $? functionality

	// Print the arguments
	while (args[i])
	{
    	write(STDOUT_FILENO, args[i], strlen(args[i]));
    	if (args[i + 1])
        	write(STDOUT_FILENO, " ", 1);
    	i++;
	}

	if (n_line)
    	write(STDOUT_FILENO, "\n", 1);
	while (tools->debug_mode)
    {
        printf("[DEBUG] ft_echo: %s\n", args[i]);
        i++;
    }
}

void ft_export(char **args, t_tools *tools)
{
    int i = 1;
    while (args[i])
    {
        // Check if the argument is a valid environment variable name
        char *equals = strchr(args[i], '=');
        if (equals)
        {
            *equals = '\0';
            setenv(args[i], equals + 1, 1);
            *equals = '=';
        }
        else
        {
            // If no '=' is found, set the variable with an empty value
            setenv(args[i], "", 1);
        }
        i++;
    }
    if (tools->debug_mode)
    {
        printf("[DEBUG]: ft_export() executed\n");
    }
}

void ft_unset(char **args, t_tools *tools)
{
    int i = 1;
    while (args[i])
    {
        unsetenv(args[i]);
        i++;
    }
    if (tools->debug_mode)
    {
        printf("[DEBUG]: ft_unset() executed\n");
    }
}

void ft_env(t_tools *tools)
{
    extern char **environ;
    char **env = environ;

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

void ft_exit(t_tools *tools)
{
    if (tools->debug_mode)
    {
        printf("[DEBUG]: ft_exit() executed\n");
    }
    exit(0);
}

void execute_builtins(t_tools *tools)
{
	t_ast *cmd_node = tools->tree;
	if (cmd_node->token == T_CMD && cmd_node->b_cmd)
	{
		if (ft_strcmp(cmd_node->str, "echo") == 0)
			ft_echo(&tools->args, tools);
		else if (ft_strcmp(cmd_node->str, "cd") == 0)
			ft_cd(&tools->args[1], tools);
		else if (ft_strcmp(cmd_node->str, "pwd") == 0)
			ft_pwd(tools);
		else if (ft_strcmp(cmd_node->str, "export") == 0)
			ft_export(&tools->args, tools);
		else if (ft_strcmp(cmd_node->str, "unset") == 0)
			ft_unset(&tools->args, tools);
		else if (ft_strcmp(cmd_node->str, "env") == 0)
			ft_env(tools);
		else if (ft_strcmp(cmd_node->str, "exit") == 0)
			ft_exit(tools);
		// add remaining builtins if any
	}
}