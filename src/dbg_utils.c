/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:23:26 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 12:29:49 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	print_tokens(t_lexer *lexer_list)
{
	t_lexer	*curr;

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

