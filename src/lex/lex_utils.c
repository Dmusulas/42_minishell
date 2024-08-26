/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:35 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/26 13:33:11 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer_parser.h"

t_lexer	*make_tk(char *str, t_tokens token)
{
	t_lexer	*new_token;

	new_token = malloc(sizeof(t_lexer));
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

	if (!*lexer_list)
	{
		*lexer_list = new_token;
		return ;
	}
	curr = *lexer_list;
	while (curr->next)
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
