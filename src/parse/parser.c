/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:46 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/03 22:28:31 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/*
	if single quote -> return trimmed str
	if double quotes-> trim and check if '$' found
		expand if needed -> return trim / expanded str
	if no quotes but '$' found
		return expanded str
	otherwise just return duplicate of src str
*/
static char	*trim_expd_arg(const char *s)
{
	size_t	len;
	char	*trim;

	len = ft_strlen(s);
	if (s[0] == '\'' && s[len - 1] == '\'')
		return (ft_strndup(s + 1, len - 2));
	if (s[0] == '"' && s[len - 1] == '"')
	{
		trim = ft_strndup(s + 1, len - 2);
		if (!trim)
			return (NULL);
		// if (ft_strchr(trim , '$'))
		// {
		// 	expd = expand_var(trim);
		// 	free(trim);
		// 	return (expd);
		// }
		return (trim);
	}
	// if (ft_str(s, '$'))
	// 	return (expand_var(s));
	return (ft_strdup(s));
}

static void	parse_arg(t_ast *cmd_node, t_tools *tools)
{
	t_lexer	*curr;
	t_ast	*arg_nd;
	t_ast	*prev_nd;

	curr = tools->lexer_lst;
	arg_nd = NULL;
	prev_nd = cmd_node;
	while (curr && (curr->token == T_CMD || curr->token == T_ARG))
	{
		arg_nd = ast_new();
		if (!arg_nd)
			return ;
		arg_nd->token = curr->token;
		arg_nd->str = trim_expd_arg(curr->str);
		// Attach the argument node to the right of the last node (cmd or previous arg)
		prev_nd->right = arg_nd;
		prev_nd = arg_nd;
		// Move to the next lexer token
		curr = curr->next;
	}
	// Update the lexer list pointer in tools
	tools->lexer_lst = curr;
}

/*
parse_cmd
	Parses a command or argument from the lexer tokens
	and constructs an AST (Abstract Syntax Tree) node.

assignes current lexer token to the node
checks if token is a builtin (set flag 'b_cmd = true')

If the token is an argument,
	processes the argument string, handling any necessary expansions
	or quote removals, updates the node's lexer string accordingly.
returns the created AST node or NULL if memory allocation fails.
 */
t_ast	*parse_cmd(t_tools *tools)
{
	t_ast	*cmd_node;

	if (!tools->lexer_lst)
		return (NULL);
	cmd_node = ast_new();
	if (!cmd_node)
		return (NULL);
	cmd_node->token = tools->lexer_lst->token;
	cmd_node->str = trim_expd_arg(tools->lexer_lst->str);
	if (!cmd_node->str)
		return (NULL);
	if (is_builtin(tools->lexer_lst->str))
	{
		cmd_node->token = T_CMD;
		cmd_node->b_cmd = true;
		// printf(" [ Debug: %s b_cmd = true ]\n", cmd_node->str);
	}
	// cmd_node->token = tools->lexer_lst->token;
	// cmd_node->str =ft_strdup(tools->lexer_lst->str);
	tools->lexer_lst = tools->lexer_lst->next;
	parse_arg(cmd_node, tools);
	return (cmd_node);
}

t_ast	*parse_pipe(t_tools *tools)
{
	t_ast	*left_node;
	t_ast	*right_node;
	t_ast	*pipe_node;

	left_node = parse_cmd(tools);
	if (!left_node)
		return (NULL);
	while (tools->lexer_lst && tools->lexer_lst->token == T_PIPE)
	{
		tools->pipes--;
		pipe_node = ast_new();
		if (!pipe_node)
			return (NULL);
		pipe_node->token = T_PIPE;
		pipe_node->str = ft_strdup("|");
		// Move to the next token (after the pipe)
		tools->lexer_lst = tools->lexer_lst->next;
		right_node = parse_cmd(tools);
		if (!right_node)
		{
			free_ast(pipe_node);
			return (NULL);
		}
		// set up childern
		pipe_node->left = left_node;
		pipe_node->right = right_node;
		// curr pipe node becomes left node for next iter
		left_node = pipe_node;
	}
	// return to root node
	return (left_node);
}

/*
TODO: adjust parse_redir and helper functions to take t_tools *tools
*/

/**
 * make_redir - Creates a new AST node for a redirection.
 * @cmd_node: The command node to which the redirection applies.
 * @token: The current lexer token representing the redirection operator.
 * @file_str: The string representing the file for redirection.
 *
 * Returns a pointer to the new redirection node, or NULL on failure.
 */
static t_ast	*make_redir(t_ast *cmd_node, t_lexer *token, char *file_str)
{
	t_ast	*redir_node;

	redir_node = ast_new();
	if (!redir_node)
	{
		free_ast(cmd_node);
		return (NULL);
	}
	redir_node->token = token->token;
	redir_node->left = cmd_node;
	if (file_str != NULL)
		redir_node->file = ft_strdup(file_str);
	if (!redir_node->file)
	{
		free_ast(redir_node);
		return (NULL);
	}
	return (redir_node);
}

/*
 * parse_redir
	- Parses command redirections from the lexer tokens and constructs
 *               an AST (Abstract Syntax Tree) representing the command with
 *               associated redirections.
 * @tokens: A pointer to the lexer tokens linked list.
 *
 * This function starts by parsing a command and then checks if the next token
 * represents a redirection (`<`, `>`, `>>`,
	or `<<`). For each redirection found,
 * it creates a new AST node to represent the redirection, with the left child
 * pointing to the command or previous redirection node, and the `file` field
 * storing the redirection target (e.g., a file name). The function returns the
 * root of the redirection AST or NULL if memory allocation fails. If any step
 * fails, it frees the previously allocated nodes to avoid memory leaks.
 */
t_ast	*parse_redir(t_tools *tools)
{
	t_ast	*cmd_node;
	t_lexer	*curr;

	cmd_node = parse_cmd(tools);
	if (!cmd_node)
		return (NULL);
	curr = tools->lexer_lst;
	while (curr && (token_check(curr->token)))
	{
		if (curr->next == NULL)
		{
			free_ast(cmd_node);
			return (NULL);
		}
		cmd_node = make_redir(cmd_node, curr, curr->next->str);
		if (!cmd_node)
			return (NULL);
		curr = curr->next->next;
	}
	tools->lexer_lst = curr;
	return (cmd_node);
}
