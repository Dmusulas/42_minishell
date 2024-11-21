/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:54 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/08 17:19:45 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

bool	is_redirection(t_tokens tk)
{
	return (tk == T_REDIR_IN || tk == T_REDIR_OUT || tk == T_APPEND
		|| tk == T_HEREDOC);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

t_ast	*ast_new(t_tools *tools)
{
	t_ast	*new_nd;

	new_nd = malloc(sizeof(t_ast));
	if (!new_nd)
	{
		ft_error(ERR_MALLOC_FAIL, tools);
		return (NULL);
	}
	new_nd->str = NULL;
	new_nd->token = 0;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->file = NULL;
	new_nd->b_cmd = false;
	return (new_nd);
}

t_ast	*ast_add_child(t_ast *parent, bool is_right, t_tools *tools)
{
	t_ast	*new_nd;

	new_nd = ast_new(tools);
	if (!new_nd)
		return (NULL);
	if (is_right)
		parent->right = new_nd;
	else
		parent->left = new_nd;
	return (new_nd);
}

/**
 * Processes an argument string: removes quotes and expands variables.
 *
 * @param s The argument string.
 * @param tools The tools structure containing environment variables.
 * @return The processed string or NULL on failure.
 */
char	*trim_expd_arg(const char *s, t_tools *tools)
{
	char	*result;
	char	*temp;
	int		i;
	int		j;
	char	quote_type;

	if (!s)
		return (NULL);
	if ((s[0] == '\'' || s[0] == '"') && s[0] == s[ft_strlen(s) - 1])
	{
		if (s[0] == '\'')
		{
			tools->in_single_quotes = true;
			return (ft_substr(s, 1, ft_strlen(s) - 2));
		}
		if (s[0] == '"')
		{
			temp = ft_substr(s, 1, ft_strlen(s) - 2);
			result = expand_var(temp, tools);
			free(temp);
			return (result);
		}
	}
	temp = ft_strdup(s);
	if (!temp)
		return (NULL);
	result = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (free(temp), NULL);
	i = 0;
	j = 0;
	quote_type = '\0';
	while (temp[i])
	{
		if ((temp[i] == '\'' || temp[i] == '"') && quote_type == '\0')
			quote_type = temp[i];
		else if (temp[i] == quote_type)
			quote_type = '\0';
		else
			result[j++] = temp[i];
		i++;
	}
	free(temp);
	if (result[0] == '\0')
	{
		free(result);
		return (expand_var(s, tools));
	}
	temp = expand_var(result, tools);
	free(result);
	return (temp);
}
