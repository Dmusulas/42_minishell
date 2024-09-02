/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:23:26 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 16:30:24 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	if (node->lexer)
		printf("Node: %s, Token: %d\n", node->lexer->str, node->lexer->token);

	if (node->file)
		printf("Redirection file: %s\n", node->file);
}

// Function to print the AST recursively
void	print_ast(t_ast *tree, int depth)
{
	while (tree != NULL)
	{
		// Print indentation based on depth
		int i = 0;
		while (i < depth)
		{
			printf("  ");
			i++;
		}
		// Print the current node
		print_ast_node(tree);
		// Print the left subtree if it exists
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
		// Print the right subtree if it exists
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
		// Break the loop as we're done processing the tree
		break ;
	}
}
