/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:32 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/22 16:57:59 by clinggad         ###   ########.fr       */
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

/*
0: no quote, 34: double quote, 39: single quote
*/
static int handle_arg(char *s, int start, t_tools *tools)
{
	int		i;
	int		q_type;
	char	*arg;

	i = start;
	q_type = 0;
	while (s[i] && (q_type || (s[i] != ' ' && !check_tk(s[i]))))
	{
		if (s[i] == 34 || s[i] == 39)
		{
			if (q_type == 0)
				q_type = s[i];
			else if (q_type == s[i])
				q_type = 0;
		}
		i++;
	}
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

int	tokenize_input(t_tools *tools)
{
	int		i;
	int		offset;

	i = 0;
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
