/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:29:03 by pmolzer           #+#    #+#             */
/*   Updated: 2024/12/01 16:01:35 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "lexer_parser.h"
#include "minishell.h"

int	check_tk(char tk)
{
	if (tk == '|' || tk == '<' || tk == '>')
		return (1);
	return (0);
}

void	handle_final_token(t_tools *tools, int start, int i, bool is_cmd)
{
	char	*token;

	if (i > start)
	{
		token = ft_substr(tools->args, start, i - start);
		if (is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
	}
}

int	check_quote_status(char *args, int *i, char *quote_type)
{
	if (*quote_type == '\0')
	{
		if (args[*i] == '"' || args[*i] == '\'')
		{
			*quote_type = args[*i];
			(*i)++;
			return (1);
		}
	}
	else
	{
		if (args[*i] == *quote_type)
		{
			*quote_type = '\0';
			(*i)++;
			return (1);
		}
	}
	return (0);
}
