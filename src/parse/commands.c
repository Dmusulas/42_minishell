/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:49:09 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/23 12:05:57 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/**
 * Processes an argument string: removes quotes and expands variables.
 *
 * @param s The argument string.
 * @param tools The tools structure containing environment variables.
 * @return The processed string or NULL on failure.
 */
static char	*trim_expd_arg(const char *s, t_tools *tools)
{
	char	*result;
	char	*temp;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	temp = ft_strdup(s);
	if (!temp)
		return (NULL);
	result = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (free(temp), NULL);
	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i] != '\'' && temp[i] != '"')
			result[j++] = temp[i];
		i++;
	}
	free(temp);
	if (result[0] == '\0')
		return (expand_var(s, tools));
	return (expand_var(result, tools));
}

/**
 * Parses arguments for a command node and attaches them to the right.
 *
 * @param cmd_node The command node to attach arguments to.
 * @param tools The tools structure containing lexer and other resources.
 */
static void	parse_arg(t_ast *cmd_node, t_tools *tools)
{
	t_lexer	*curr;
	t_ast	*prev_node;
	t_ast	*arg_node;

	curr = tools->lexer_lst;
	prev_node = cmd_node;
	while (curr && (curr->token == T_CMD || curr->token == T_ARG))
	{
		arg_node = ast_new(tools);
		if (!arg_node)
			return ;
		arg_node->token = curr->token;
		arg_node->str = trim_expd_arg(curr->str, tools);
		prev_node->right = arg_node;
		prev_node = arg_node;
		curr = curr->next;
	}
	tools->lexer_lst = curr;
}

/**
 * Parses a command or argument and creates the corresponding AST node.
 *
 * @param tools The tools structure containing lexer and other resources.
 * @return The created command node or NULL on failure.
 */
t_ast	*parse_cmd(t_tools *tools)
{
	t_ast	*cmd_node;

	cmd_node = ast_new(tools);
	if (!cmd_node)
		return (NULL);
	cmd_node->token = tools->lexer_lst->token;
	cmd_node->str = trim_expd_arg(tools->lexer_lst->str, tools);
	if (!cmd_node->str)
		return (free_ast(cmd_node), NULL);
	if (is_builtin(tools->lexer_lst->str))
		cmd_node->b_cmd = true;
	tools->lexer_lst = tools->lexer_lst->next;
	parse_arg(cmd_node, tools);
	return (cmd_node);
}
