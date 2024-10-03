/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/03 12:21:27 by pmolzer          ###   ########.fr       */
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
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
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
 * This function iterates through the input string, skipping spaces,
	identifying tokens,
	and adding them to the lexer list. It processes tokens in the following order:
	1. Two-character tokens (e.g., '>>', '<<')
	2. Single-character tokens (e.g., '|', '<', '>')
	3. General arguments (including quoted arguments)

	* The function maintains a flag `is_new_cmd` to determine whether the current token is a new command or an argument to the previous command.

	* This flag is reset after processing a token that indicates the start of a new command (e.g.,
	'|', '<', '>', '>>', '<<').
 *
 * Returns 1 on success.
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
