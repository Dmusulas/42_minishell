/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:09:58 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 14:43:46 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

static t_ast	*ast_new(void)
{
	t_ast	*new_nd;

	new_nd = malloc(sizeof(t_ast));
	if (!new_nd)
	{
		perror("malloc ast");
		return (NULL);
	}
	new_nd->lexer = NULL;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->file = NULL;
	new_nd->b_cmd = false;
	return (new_nd);
}

/*
	if single quote -> return trimmed str
	if double quotes-> trim and check if '$' found
		expand if needed -> return trim / expanded str
	if no quotes but '$' found
		return expanded str
	otherwise just return duplicate of src str
*/
char	*parse_arg(const char *s)
{
	size_t	len;
	char	*trim;
	char	*expd;

	len = ft_strlen(s);
	if(s[0] == '\'' && s[len - 1] == '\'')
		return (ft_strndup(s + 1, len - 2));
	if (s[0] == '"' && s[len - 1] == '"')
	{
		trim = ft_strndup(s + 1, len - 2);
		if (ft_strchr(trim , '$'))
		{
			expd = expand_var(trim);
			free(trim);
			return (expd);
		}
		return (trim);
	}
	if (ft_str(s, '$'))
		return (expand_var(s));
	return (ft_strdup(s));
}


t_ast	*parse_cmd(t_lexer **tokens)
{
	t_ast	*cmd_node;
	char	*new_str;

	cmd_node = new_ast();
	if (!cmd_node)
		return (NULL);
	cmd_node->lexer = *tokens;
	*tokens = (*tokens)->next;
	if (cmd_node->lexer->token == T_CMD
		&& (is_builtin(cmd_node->lexer->str)))
			cmd_node->b_cmd = true;
	if (cmd_node->lexer->token == T_ARG)
	{
		new_str = parse_arg(cmd_node->lexer->str);
		if (new_str != cmd_node->lexer->str)
		{
			free(cmd_node->lexer->str);
			cmd_node->lexer->str = new_str;
		}
		else
			free(new_str);
	}
	return (cmd_node);
}

t_ast	*parse_pipe(t_lexer **tokens)
{
	
}

t_ast	*parse_redir(t_lexer **token)
{
	
}