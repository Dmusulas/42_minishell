/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:32 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/23 15:59:43 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tk(char tk)
{
	if (tk == '|' || tk == '<' || tk == '>')
		return (1);
	else
		return (0);
}

static int handle_q_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	q_type;
	char	*arg;

	i = start;
	q_type = s[i++];
	
	while (s[i] && s[i] != q_type)
		i++;
	// Extract the argument, excluding the quotes
	arg = ft_substr(s, start + 1, i - start - 1);
	if (arg == NULL)
	{
		perror("ft_substr");
		return (0);
	}
	add_tk(&(tools->lexer_lst), make_tk(arg, T_ARG));
	return (i - start + 1);  // Include the closing quote
}

static int handle_arg(char *s, int start, t_tools *tools)
{
	int		i;
	char	*arg;

	i = start;
	if (s[i] == 34 || s[i] == 39)
		return (handle_q_arg(s, i, tools));
	while (s[i] && s[i] != ' ' && !check_tk(s[i]))
		i++;
	arg = ft_substr(s, start, i - start);
	if (arg == NULL)
	{
		perror("ft_substr");
		return (0);
	}
	add_tk_cmd_check(arg, tools);
	return (i - start);
}

static int	skip_space(char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

int tokenize_input(t_tools *tools)
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
	// label_cmds(tools);
	return (1);
}
