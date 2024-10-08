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
#include "libft.h"
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

/**
 * Recursively prints the AST structure with proper indentation.
 *
 * @param tree The current node in the AST.
 * @param depth The current depth level in the tree.
 */
void	print_ast(t_ast *tree, int depth)
{
	int	i;

	if (!tree)
		return ;
	for (i = 0; i < depth; i++)
		printf("  ");
	print_ast_node(tree);
	if (tree->left)
	{
		for (i = 0; i < depth + 1; i++)
			printf("  ");
		printf("Left:\n");
		print_ast(tree->left, depth + 1);
	}
	if (tree->right)
	{
		for (i = 0; i < depth + 1; i++)
			printf("  ");
		printf("Right:\n");
		print_ast(tree->right, depth + 1);
	}
}

void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

void	print_linkedlist(t_list *lst)
{
	ft_lstiter(lst, print_content);
}

void	test_envp(t_list *envp)
{
	update_or_add_envp(&envp, "AAAA=TOP");
	update_or_add_envp(&envp, "COLORTERM=tEST");
	update_or_add_envp(&envp, "colorterm=tEST");
	update_or_add_envp(&envp, "val=hehe");
	update_or_add_envp(&envp, "___MEH=bot");
	print_linkedlist(envp);
}
