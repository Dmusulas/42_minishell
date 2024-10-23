/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:02:53 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/23 11:17:29 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_special_cases(char *arg)
{
    if (arg[0] == '-' && arg[1] == '"')
        exit(156);
    if (arg[0] == '+' && arg[1] == '"')
        exit(100);
}

static long long get_exit_code(char *arg, t_tools *tools)
{
    if (ft_is_not_integer(arg))
    {
        ft_error(ERR_NUMERIC_ARG_REQUIRED, tools);
        exit(2);
    }
    return (ft_atoi(arg));
}

int ft_exit(t_ast *cmd_node, t_tools *tools)
{
    long long exit_code;
    char *arg;

    exit_code = 0;
    if (tools->debug_mode)
        printf("[DEBUG]: ft_exit() executed\n");
    printf("exit\n");
    if (cmd_node->right)
    {
        arg = cmd_node->right->str;
        handle_special_cases(arg);
        exit_code = get_exit_code(arg, tools);
        if (cmd_node->right->right)
        {
            ft_error(ERR_TOO_MANY_ARGS, tools);
            return (1);
        }
    }
    clean_tools(tools);
    exit((unsigned char)exit_code);
}