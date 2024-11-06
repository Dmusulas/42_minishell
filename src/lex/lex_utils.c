/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:28 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/06 16:37:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "libft.h"
#include "error_messages.h"
/*
 * This function calculates the length of the initial segment of string `s`
 * that contains no characters from string `reject`. It checks each character
 * in `s` to see if it appears in `reject`. If a match is found, it returns
 * the index of that character in `s`. If no match is found, it returns the
 * length of `s`. This function helps tokenize input strings in a shell parser
 * by identifying the first character that is not part of the current token.
 */
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

t_lexer	*make_tk(char *str, t_tokens token)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
	{
		perror("malloc");
		return (NULL);
	}
	new_token->str = str;
	new_token->token = token;
	new_token->next = NULL;
	return (new_token);
}

void	add_tk(t_lexer **lexer_list, t_lexer *new_token)
{
	t_lexer	*curr;

	curr = *lexer_list;
	if (!*lexer_list)
	{
		*lexer_list = new_token;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_token;
}

int	ft_one_tk(char c, t_tools *tools)
{
	if (c == '|')
		add_tk(&(tools->lexer_lst), make_tk(ft_strdup("|"), T_PIPE));
	else if (c == '<')
		add_tk(&(tools->lexer_lst), make_tk(ft_strdup("<"), T_REDIR_IN));
	else if (c == '>')
		add_tk(&(tools->lexer_lst), make_tk(ft_strdup(">"), T_REDIR_OUT));
	return (1);
}

int	ft_two_tk(char c1, char c2, t_tools *tools)
{
	if (c1 == '<' && c2 == '<')
	{
		add_tk(&(tools->lexer_lst), make_tk(ft_strdup("<<"), T_HEREDOC));
		return (2);
	}
	else if (c1 == '>' && c2 == '>')
	{
		add_tk(&(tools->lexer_lst), make_tk(ft_strdup(">>"), T_APPEND));
		return (2);
	}
	return (0);
}

/*
 * This function checks for unclosed quotes in a given string.
 * It iterates through the string, toggling a quote type when it encounters
 * a quote character. If it finds an unmatched quote at the end, it reports
 * an error and returns 0; otherwise, it returns 1 indicating all quotes are closed.
 */
int	check_quotes(char *s, t_tools *tools)
{
	int	i;
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
