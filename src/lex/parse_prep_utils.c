/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prep_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:37 by dmusulas          #+#    #+#             */
/*   Updated: 2024/12/01 16:04:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	process_tokens(t_tools *tools)
{
	t_lexer	*curr;

	if (tools->lexer_lst == NULL)
		return ;
	curr = tools->lexer_lst;
	while (curr)
	{
		if (is_redirection(curr->token))
		{
			if (curr->token == T_HEREDOC)
				tools->heredoc = true;
		}
		curr = curr->next;
	}
}

void	handle_input(t_tools *tools)
{
	if (!check_quotes(tools->args, tools))
	{
		tools->last_exit_status = 1;
		return ;
	}
	if (!tokenize_input(tools))
		ft_error(ERR_LEX, tools);
	if (tools->lexer_lst != NULL)
	{
		process_tokens(tools);
		parse_input(tools);
	}
}
