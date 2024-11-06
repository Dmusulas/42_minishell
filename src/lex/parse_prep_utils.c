/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prep_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:37 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/06 15:29:04 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/*
	set p_redir as whole command,
		not sure how to handle this if there is a pipe.
	parser splits commands to exec
*/
void	process_tokens(t_tools *tools)
{
	t_lexer	*curr;

	if (tools->lexer_lst == NULL)
		return ;
	curr = tools->lexer_lst;
	while (curr)
	{
		if (token_check(curr->token))
		{
			// tools->p_redir = curr;
			// not sure if redir ptr should be assigned here
			tools->redir_num++;
			if (curr->token == T_HEREDOC)
				tools->heredoc = true;
		}
		else if (curr->token == T_PIPE)
			tools->pipes++;
		curr = curr->next;
	}
}

void	handle_input(t_tools *tools)
{
	t_lexer	*orig_lexer_lst;

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
		orig_lexer_lst = tools->lexer_lst;
		if (!parse_input(tools))
			ft_error(ERR_PAR, tools);
		if (tools->tree && tools->debug_mode)
			print_tokens(orig_lexer_lst);
	}
}
