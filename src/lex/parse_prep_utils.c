/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prep_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:01:37 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:01:37 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

// static t_tokens	arg_check(char *token)
// {
// 	if (is_builtin(token))
// 		return (T_CMD);
// 	return (T_ARG);
// }

// void	add_tk_cmd_check(char *str, t_tools *tools)
// {
// 	t_tokens	token_type;

// 	token_type = arg_check(str);
// 	add_tk(&(tools->lexer_lst), make_tk(str, token_type));
// }

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
	while (curr != NULL)
	{
		if (token_check(curr->token))
		{
			// tools->p_redir = curr;
				//not sure if redir ptr should be assigned here
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

	if (!check_quotes(tools->args))
		ft_error(ERR_QUO, tools);
	if (!tokenize_input(tools))
		ft_error(ERR_LEX, tools);
	if (tools->lexer_lst != NULL)
	{
		process_tokens(tools);
		printf("   lexer list after process_tokens:\n");
		print_tokens(tools->lexer_lst);
		orig_lexer_lst = tools->lexer_lst;
		if (!parse_input(tools))
			ft_error(ERR_PAR, tools);
		if (tools->tree)
		{
			printf("   lexer list after parsing:\n");
			print_tokens(orig_lexer_lst);
			printf("   printing ast tree:\n");
			print_ast(tools->tree, 0);
		}
	}
}
