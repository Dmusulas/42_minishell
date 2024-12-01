/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:30:49 by pmolzer           #+#    #+#             */
/*   Updated: 2024/12/01 16:34:23 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

char	*handle_quoted_string(const char *s, t_tools *tools)
{
	char	*temp;
	char	*result;

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
	return (NULL);
}

char	*remove_quotes(const char *temp)
{
	char	*result;
	int		i;
	int		j;
	char	quote_type;

	result = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	if (!result)
		return (NULL);
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
	return (result);
}

char	*process_unquoted_string(const char *s, t_tools *tools)
{
	char	*temp;
	char	*result;
	char	*final;

	temp = ft_strdup(s);
	if (!temp)
		return (NULL);
	result = remove_quotes(temp);
	free(temp);
	if (!result)
		return (NULL);
	if (result[0] == '\0')
	{
		free(result);
		return (expand_var(s, tools));
	}
	final = expand_var(result, tools);
	free(result);
	return (final);
}
