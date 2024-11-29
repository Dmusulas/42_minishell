/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/29 18:27:59 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

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

static void	handle_final_token(t_tools *tools, int start, int i, bool is_cmd)
{
	char	*token;

	if (i > start)
	{
		token = ft_substr(tools->args, start, i - start);
		if (is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
	}
}

static void	handle_space_token(t_tools *tools, int *i, int *start, bool *is_cmd)
{
	char	*token;

	if (*i > *start)
	{
		token = ft_substr(tools->args, *start, *i - *start);
		if (*is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
		*is_cmd = false;
	}
	*start = *i + 1;
	(*i)++;
}

static void	handle_special_token(t_tools *tools, int *i,
		int *start, bool *is_cmd)
{
	int		offset;
	char	*token;

	if (*i > *start)
	{
		token = ft_substr(tools->args, *start, *i - *start);
		if (*is_cmd)
			add_tk(&(tools->lexer_lst), make_tk(token, T_CMD));
		else
			add_tk(&(tools->lexer_lst), make_tk(token, T_ARG));
	}
	offset = ft_two_tk(tools->args[*i], tools->args[*i + 1], tools);
	if (offset > 0)
	{
		*i += offset;
		*start = *i;
		*is_cmd = false;
		return ;
	}
	ft_one_tk(tools->args[*i], tools);
	(*i)++;
	*start = *i;
	*is_cmd = (tools->args[*i - 1] == '|');
}

/* static int	process_lexer_tokens(char *input_str, int *i, char *quote_type)
{
	if ((input_str[*i] == '"' || input_str[*i] == '\'') && *quote_type == '\0')
		*quote_type = input_str[*i];
	else if (input_str[*i] == *quote_type)
		*quote_type = '\0';
	return (1);
} */

static int	check_quote_status(char *args, int *i, char *quote_type)
{
	if (*quote_type == '\0')
	{
		if (args[*i] == '"' || args[*i] == '\'')
		{
			*quote_type = args[*i];
			(*i)++;
			return (1);
		}
	}
	else
	{
		if (args[*i] == *quote_type)
		{
			*quote_type = '\0';
			(*i)++;
			return (1);
		}
	}
	return (0);
}

static int	handle_token_processing_core(t_tools *tools, int *i,
	char *quote_type, bool *is_cmd)
{
	int		start;

	start = 0;
	while (tools->args[*i])
	{
		if (check_quote_status(tools->args, i, quote_type))
			continue ;
		if (tools->args[*i] == ' ' && *quote_type == '\0')
		{
			handle_space_token(tools, i, &start, is_cmd);
			continue ;
		}
		if (*quote_type == '\0' && check_tk(tools->args[*i]))
		{
			handle_special_token(tools, i, &start, is_cmd);
			continue ;
		}
		(*i)++;
	}
	handle_final_token(tools, start, *i, *is_cmd);
	if (*quote_type == '\0')
		return (1);
	return (0);
}

static int	handle_token_processing(t_tools *tools, bool *is_cmd)
{
	int		i;
	char	quote_type;

	i = 0;
	quote_type = '\0';
	return (handle_token_processing_core(tools, &i, &quote_type, is_cmd));
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
