/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:01:05 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: add checks for syntax errors near tokens

int	handle_q_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	q_type;
	char	*arg;

	i = start;
	q_type = s[i++];
	while (s[i] && s[i] != q_type)
		i++;
	arg = ft_substr(s, start + 1, i - start - 1);
	if (arg == NULL)
	{
		perror("ft_substr");
		return (0);
	}
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	return (i - start + 1);
}

static int	check_tk(char tk)
{
	if (tk == '|' || tk == '<' || tk == '>')
		return (1);
	else
		return (0);
}
/*
arg = ft_substr(s, start + 1, i - start - 1)
	Extract the argument, excluding the quotes
return (i - start + 1);
	Include the closing quote when updating index position
*/

int	handle_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	*arg;

	// t_lexer	*new_token;
	i = start;
	if (s[i] == '"' || s[i] == '\'')
		return (handle_q_arg(s, i, tools));
	while (s[i] && s[i] != ' ' && !check_tk(s[i]))
		i++;
	arg = ft_substr(s, start, i - start);
	if (arg == NULL)
	{
		perror("ft_substr");
		return (0);
	}
	// new_token = make_tk(arg, T_ARG);
	// if (new_token == NULL)
	// {
	// 	free(arg);
	// 	return (0);
	// }
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	// add_tk(&(tools->lexer_lst), new_token);
	// add_tk_cmd_check(arg, tools);
	return (i - start);
}

static int	skip_space(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

/**
 * tokenize_input
	- Tokenizes the input string and populates the lexer list in the tools struct.

	* @tools: Pointer to the tools struct containing the input string and lexer list.
 *
 * This function processes the input string from the tools struct,
	breaking it down
 * into tokens that represent commands, arguments, operators,
	etc. It iterates through
 * the input string, skipping spaces, identifying tokens,
	and adding them to the lexer list.
 * Depending on the character or sequence of characters encountered,
	it either processes
 * a two-character token, a single-character token, or a general argument.
 *
 * Returns 1 on success.
 */
int	tokenize_input(t_tools *tools)
{
	int	i;
	int	offset;

	i = 0;
	tools->lexer_lst = NULL;
	while (tools->args[i])
	{
		i = skip_space(tools->args, i);
		if (tools->args[i] == '\0')
			break ;
		offset = ft_two_tk(tools->args[i], tools->args[i + 1], tools);
		if (offset > 0)
			i += offset;
		else if (check_tk(tools->args[i]))
			i += ft_one_tk(tools->args[i], tools);
		else
			i += handle_arg(tools->args, i, tools);
	}
	return (1);
}
