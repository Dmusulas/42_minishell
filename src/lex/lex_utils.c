/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:28 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 22:26:27 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "libft.h"

/*
 * This function calculates the length of the initial segment of string `s` which
 * contains only characters not in string `reject`. It iterates through each character
 * in `s` and checks if it is present in `reject`. If a character from `s` is found in
 * `reject`, the function returns the index of that character in `s`. If no characters
 * from `s` are found in `reject`, the function returns the length of `s`.
 * 
 * This function is necessary for tokenizing input strings in the context of a shell
 * parser. It helps to identify the start of a token by finding the first character
 * that is not part of the current token. For example, in a string like "ls -l", it
 * would return the index of the first space character, indicating the end of the
 * command token "ls".
 */
size_t ft_strcspn(const char *s, const char *reject)
{
    size_t i;
    size_t j;

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

int	check_quotes(char *s)
{
	int	i;
	int	q_q;
	int	q;

	q_q = 0;
	q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
			q_q += 1;
		if (s[i] == 39)
			q += 1;
		i++;
	}
	if ((q_q > 0 && q_q % 2 != 0) || (q > 0 && q % 2 != 0))
		return (0);
	else
		return (1);
}
