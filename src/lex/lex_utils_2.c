/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:38:42 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/27 22:38:42 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_messages.h"
#include "lexer_parser.h"

/*
 * This function checks for unclosed quotes in a given string.
 * It iterates through the string, toggling a quote type when it encounters
 * a quote character. If it finds an unmatched quote at the end, it reports
 * an error and returns 0; otherwise,
	it returns 1 indicating all quotes are closed.
 */
int	check_quotes(char *s, t_tools *tools)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = 0;
	while (s[i])
	{
		if (!quote_type && (s[i] == '"' || s[i] == '\''))
			quote_type = s[i];
		else if (s[i] == quote_type)
			quote_type = 0;
		i++;
	}
	if (quote_type)
	{
		ft_error(ERR_QUO, tools);
		return (0);
	}
	return (1);
}
