/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:34:21 by pmolzer           #+#    #+#             */
/*   Updated: 2024/11/29 18:35:13 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "lexer_parser.h"
#include "minishell.h"

void	handle_space_token(t_tools *tools, int *i, int *start, bool *is_cmd)
{
	char	*token;

	if (*i > *start)
	{
		token = ft_substr(tools->args, *start, *i - *start);
		if (*is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
		*is_cmd = false;
	}
	*start = *i + 1;
	(*i)++;
}

void	handle_special_token(t_tools *tools, int *i,
		int *start, bool *is_cmd)
{
	int		offset;
	char	*token;

	if (*i > *start)
	{
		token = ft_substr(tools->args, *start, *i - *start);
		if (*is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
	}
	offset = ft_two_tk(tools->args[*i], tools->args[*i + 1], tools);
	if (offset > 0)
	{
		*i += offset;
		*start = *i;
		*is_cmd = false;
		return ;
	}
	ft_one_tk(tools->args[*i], tools);
	(*i)++;
	*start = *i;
	*is_cmd = (tools->args[*i - 1] == '|');
}

int	handle_token_processing_core(t_tools *tools, int *i,
	char *quote_type, bool *is_cmd)
{
	int		start;

	start = 0;
	while (tools->args[*i])
	{
		if (check_quote_status(tools->args, i, quote_type))
			continue ;
		if (tools->args[*i] == ' ' && *quote_type == '\0')
		{
			handle_space_token(tools, i, &start, is_cmd);
			continue ;
		}
		if (*quote_type == '\0' && check_tk(tools->args[*i]))
		{
			handle_special_token(tools, i, &start, is_cmd);
			continue ;
		}
		(*i)++;
	}
	handle_final_token(tools, start, *i, *is_cmd);
	if (*quote_type == '\0')
		return (1);
	return (0);
}

int	handle_token_processing(t_tools *tools, bool *is_cmd)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = '\0';
	return (handle_token_processing_core(tools, &i, &quote_type, is_cmd));
}
