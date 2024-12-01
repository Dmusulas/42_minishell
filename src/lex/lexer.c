/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 15:30:54 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_quote(char *s, int start, char quote, char **arg)
{
	int		i;
	char	*temp;

	i = start + 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] != quote)
		return (-1);
	temp = ft_substr(s, start, i - start + 1);
	if (!temp)
		return (-1);
	*arg = ft_strjoin_free(*arg, temp);
	free(temp);
	return (i - start + 1);
}

int	handle_q_arg(char *s, int start, t_tools *tools)
{
	int		i;
	int		total_len;
	char	*arg;
	int		quote_len;

	i = start;
	total_len = 0;
	arg = ft_strdup("");
	while (s[i] && (s[i] == '"' || s[i] == '\''))
	{
		quote_len = handle_single_quote(s, i, s[i], &arg);
		if (quote_len == -1)
		{
			free(arg);
			return (ft_error(ERR_SYNTAX, tools));
		}
		i += quote_len;
		total_len += quote_len;
		if (s[i] != '"' && s[i] != '\'')
			break ;
	}
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	return (total_len);
}

/**
 * Handles general arguments, including quoted arguments and regular words.
 *
 * @param s The input string containing the argument.
 * @param start The index where the argument starts.
 * @param tools The tools structure containing lexer list.
 * @return The length of the processed argument,
	or an error code if allocation fails.
 */
int	handle_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	*arg;

	i = start;
	if (s[i] == '"' || s[i] == '\'')
		return (handle_q_arg(s, i, tools));
	while (s[i] && s[i] != ' ' && !check_tk(s[i]))
		i++;
	arg = ft_substr(s, start, i - start);
	if (!arg)
		return (ft_error(ERR_MALLOC_FAIL, tools));
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	return (i - start);
}

int	tokenize_input(t_tools *tools)
{
	bool	is_cmd;
	int		result;

	is_cmd = true;
	tools->lexer_lst = NULL;
	result = handle_token_processing(tools, &is_cmd);
	if (!result)
		return (ft_error(ERR_SYNTAX, tools));
	return (1);
}
