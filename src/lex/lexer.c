/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:01:51 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
