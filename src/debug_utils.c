/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:53 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/22 13:18:18 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	print_tokens(t_lexer *lexer_list)
{
	t_lexer	*current;

	current = lexer_list;
	while (current)
	{
		if (current->str == NULL)
			printf("Token: NULL, Type: %d\n", current->token);
		else
			printf("Token: %s, Type: %d\n", current->str, current->token);
		current = current->next;
	}
}

/*
empty token list
*/
void	clear_tokens(t_lexer **lexer_list)
{
	t_lexer	*current;
	t_lexer	*next_node;

	current = *lexer_list;
	while (current)
	{
		next_node = current->next;
		if (current->str != NULL)
			free(current->str);
		free(current);
		current = next_node;
	}
	*lexer_list = NULL;
}
