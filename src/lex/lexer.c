/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 22:27:21 by pmolzer          ###   ########.fr       */
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
	t_tokens token_type;

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
	token_type = (tools->lexer_lst == NULL) ? T_CMD : T_ARG;
	add_tk(&(tools->lexer_lst), make_tk(arg, token_type));
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
 * This function iterates through the input string, skipping spaces, identifying tokens,
	and adding them to the lexer list. It processes tokens in the following order:
	1. Two-character tokens (e.g., '>>', '<<')
	2. Single-character tokens (e.g., '|', '<', '>')
	3. General arguments (including quoted arguments)
 * The function maintains a flag `is_new_cmd` to determine whether the current token is a new command or an argument to the previous command.
 * This flag is reset after processing a token that indicates the start of a new command (e.g., '|', '<', '>', '>>', '<<').
 *
 * Returns 1 on success.
 */
int	tokenize_input(t_tools *tools)
{
	int	i;
	int	offset;
	bool is_new_cmd;

	i = 0;
	is_new_cmd = true; // Initialize flag to indicate the start of a new command
	tools->lexer_lst = NULL; // Reset the lexer list
	while (tools->args[i])
	{
		i = skip_space(tools->args, i); // Skip spaces to find the next token
		if (tools->args[i] == '\0')
			break ; // Exit if end of string is reached
		offset = ft_two_tk(tools->args[i], tools->args[i + 1], tools); // Check for two-character tokens
		if (offset > 0)
		{
			i += offset; // Move index forward by the length of the token
			is_new_cmd = true; // Reset flag to indicate a new command
		}
		else if (check_tk(tools->args[i])) // Check for single-character tokens
		{
			i += ft_one_tk(tools->args[i], tools); // Process single-character token
			is_new_cmd = true; // Reset flag to indicate a new command
		}
		else // Process general arguments
		{
			if (is_new_cmd) // If this is a new command
			{
				add_tk(&(tools->lexer_lst), make_tk(ft_substr(tools->args, 
							i, ft_strcspn(&tools->args[i], " ")), T_CMD)); // Add command token
				i += ft_strcspn(&tools->args[i], " "); // Move index forward by the length of the command
				is_new_cmd = false; // Set flag to indicate this is not a new command
			}
			else // If this is an argument to the previous command
				i += handle_arg(tools->args, i, tools); // Process argument
		}
	}
	return (1); // Return success
}
