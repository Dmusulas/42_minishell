/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:53 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/23 16:10:12 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

/*
	for debug only
*/
void	print_tokens(t_lexer *lexer_list)
{
	t_lexer *curr;

	curr = lexer_list;
	while (curr)
	{
		if (curr->str == NULL)
			printf("Token: NULL, Type: %d\n", curr->token);
		else
			printf("Token: %s, Type: %d\n", curr->str, curr->token);
		curr = curr->next;
	}
}

void	clear_tokens(t_lexer **lexer_list)
{
	t_lexer *curr;
	t_lexer *next_node;

	if (lexer_list == NULL || *lexer_list == NULL)
		return ;
	curr = *lexer_list;
	while (curr)
	{
		next_node = curr->next;
		if (curr->str != NULL)
		{
			free(curr->str);
			curr->str = NULL;
		}
		free(curr);
		curr = next_node;
	}
	*lexer_list = NULL;
}

void clean_tools(t_tools *tools)
{
	if (tools->args != NULL)
	{
		free(tools->args);
		tools->args = NULL;
	}
	if (tools->lexer_lst != NULL)
		clear_tokens(&tools->lexer_lst);
	if (tools->p_redir != NULL)
	{
		free(tools->p_redir);
		tools->p_redir = NULL;
	}
}
