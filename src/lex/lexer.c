/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/29 17:38:32 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    
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
	char    *temp;
	int     total_len;

	i = start;
	total_len = 0;
	arg = ft_strdup("");
	while (s[i] && (s[i] == '"' || s[i] == '\''))
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] != quote)
			return (ft_error(ERR_SYNTAX, tools));
		temp = ft_substr(s, start + total_len, i - (start + total_len) + 1);
		if (!temp)
			return (ft_error(ERR_MALLOC_FAIL, tools));
		arg = ft_strjoin_free(arg, temp);
		free(temp);
		i++;
		total_len = i - start;
		if (s[i] != '"' && s[i] != '\'')
			break;
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

static void handle_space_token(t_tools *tools, int *i, int *start, bool *is_cmd)
{
    if (*i > *start)
    {
        char *token = ft_substr(tools->args, *start, *i - *start);
        add_tk(&(tools->lexer_lst), make_tk(token, *is_cmd ? T_CMD : T_ARG));
        *is_cmd = false;
    }
    *start = *i + 1;
    (*i)++;
}

static void handle_special_token(t_tools *tools, int *i, int *start, bool *is_cmd)
{
    int offset;

    if (*i > *start)
    {
        char *token = ft_substr(tools->args, *start, *i - *start);
        add_tk(&(tools->lexer_lst), make_tk(token, *is_cmd ? T_CMD : T_ARG));
    }
    offset = ft_two_tk(tools->args[*i], tools->args[*i + 1], tools);
    if (offset > 0)
    {
        *i += offset;
        *start = *i;
        *is_cmd = false;
        return;
    }
    ft_one_tk(tools->args[*i], tools);
    (*i)++;
    *start = *i;
    *is_cmd = (tools->args[*i - 1] == '|');
}

int tokenize_input(t_tools *tools)
{
    int     i;
    int     start;
    bool    is_cmd;
    char    quote_type;

    i = 0;
    start = 0;
    is_cmd = true;
    quote_type = '\0';
    tools->lexer_lst = NULL;

    while (tools->args[i])
    {
        if ((tools->args[i] == '"' || tools->args[i] == '\'') && quote_type == '\0')
            quote_type = tools->args[i];
        else if (tools->args[i] == quote_type)
            quote_type = '\0';
        
        if (tools->args[i] == ' ' && quote_type == '\0')
        {
            handle_space_token(tools, &i, &start, &is_cmd);
            continue;
        }
        if (quote_type == '\0' && check_tk(tools->args[i]))
        {
            handle_special_token(tools, &i, &start, &is_cmd);
            continue;
        }
        i++;
    }
    if (i > start)
    {
        char *token = ft_substr(tools->args, start, i - start);
        add_tk(&(tools->lexer_lst), make_tk(token, is_cmd ? T_CMD : T_ARG));
    }
    return (quote_type == '\0' ? 1 : ft_error(ERR_SYNTAX, tools));
}
