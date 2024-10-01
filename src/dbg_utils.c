/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:23:26 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/06 13:46:20 by clinggad         ###   ########.fr       */
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

// Function to print a single AST node
void	print_ast_node(t_ast *node)
{
	if (node->str)
		printf("Node: %s, Token: %d\n", node->str, node->token);
	if (node->file)
		printf("Redirection file: %s\n", node->file);
}

// Function to print the AST recursively
/*
	depth = 0 (root value)
*/
void	print_ast(t_ast *tree, int depth)
{
	int	i;

	while (tree != NULL)
	{
		i = 0;
		while (i < depth)
		{
			printf("  ");
			i++;
		}
		print_ast_node(tree);
		if (tree->left != NULL)
		{
			i = 0;
			while (i < depth + 1)
			{
				printf("  ");
				i++;
			}
			printf("Left:\n");
			print_ast(tree->left, depth + 1);
		}
		if (tree->right != NULL)
		{
			i = 0;
			while (i < depth + 1)
			{
				printf("  ");
				i++;
			}
			printf("Right:\n");
			print_ast(tree->right, depth + 1);
		}
		break ;
	}
}
