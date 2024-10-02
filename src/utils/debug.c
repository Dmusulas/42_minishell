/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:20 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:00:20 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: REMOVE BEFORE SUBMISSION

#include "lexer_parser.h"
#include "minishell.h"

void	print_tokens(t_lexer *lexer_list)
{
	t_lexer	*current;

	current = lexer_list;
	while (current)
	{
		if (current->str == NULL)
			printf("[DEBUG]: Token: NULL, Type: %d\n", current->token);
		else
			printf("[DEBUG]: Token: %s, Type: %d\n", current->str,
				current->token);
		current = current->next;
	}
}

// Function to print a single AST node
void	print_ast_node(t_ast *node)
{
	if (node->str)
		printf("[DEBUG]: Node: %s, Token: %d\n", node->str, node->token);
	if (node->file)
		printf("[DEBUG]: Redirection file: %s\n", node->file);
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
