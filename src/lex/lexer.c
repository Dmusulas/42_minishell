/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/12 18:44:05 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the given character is a token delimiter ('|', '<', or '>').
 *
 * @param tk The character to check.
 * @return 1 if the character is a token delimiter, otherwise 0.
 */
static int	check_tk(char tk)
{
	if (tk == '|' || tk == '<' || tk == '>')
		return (1);
	return (0);
}

/**
 * Handles quoted arguments (single or double quotes)
 * and extracts them from the string.
 *
 * @param s The input string containing the argument.
 * @param start The index where the quoted argument starts.
 * @param tools The tools structure containing lexer list.
 * @return The length of the processed argument,
	or an error code if allocation fails.
 */
int	handle_q_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	quote;
	char	*arg;

	i = start;
	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
	{
		if (quote == '"' && s[i] == '$')
			i++;
		else
			i++;
	}
	if (s[i] != quote)
		return (ft_error(ERR_SYNTAX, tools));
	arg = ft_substr(s, start, i - start + 1);
	if (!arg)
		return (ft_error(ERR_MALLOC_FAIL, tools));
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	return (i - start + 1);
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

/**
 * Skips spaces in the string starting from the given index.
 *
 * @param s The input string.
 * @param i The current index.
 * @return The index after skipping spaces.
 */
static int	skip_space(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

/**
 * Tokenizes the input string into commands and arguments,
	updating the lexer list.
 *
 * This function processes tokens in the following order:
 * 1. Two-character tokens (e.g., '>>', '<<')
 * 2. Single-character tokens (e.g., '|', '<', '>')
 * 3. General arguments, including quoted arguments.
 *
	* It maintains a flag `is_cmd` to determine whether the
	* current token is a new command
 * or an argument to the previous command.
 *
	* @param tools Pointer to the tools structure containing
	* the input string and lexer list.
 * @return 1 on success.
 */
int	tokenize_input(t_tools *tools)
{
	int		i;
	int		offset;
	bool	is_cmd;

	i = 0;
	is_cmd = true;
	tools->lexer_lst = NULL;
	while (tools->args[i])
	{
		i = skip_space(tools->args, i);
		if (tools->args[i] == '\0')
			break ;
		offset = ft_two_tk(tools->args[i], tools->args[i + 1], tools);
		if (offset > 0)
		{
			i += offset;
			is_cmd = false;
			continue ;
		}
		if (check_tk(tools->args[i]))
		{
			i += ft_one_tk(tools->args[i], tools);
			is_cmd = (tools->args[i - 1] == '|');
			continue ;
		}
		if (is_cmd)
		{
			add_tk(&(tools->lexer_lst), make_tk(ft_substr(tools->args, i,
						ft_strcspn(&tools->args[i], " ")), T_CMD));
			i += ft_strcspn(&tools->args[i], " ");
			is_cmd = false;
		}
		else
		{
			i += handle_arg(tools->args, i, tools);
		}
	}
	return (1);
}
