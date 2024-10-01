/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:53 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/10 13:48:11 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

void	clear_tokens(t_lexer **lexer_list)
{
	t_lexer	*curr;
	t_lexer	*next_node;

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

// Function to free the AST nodes
/*
FREE AST TREE
	free child nodes (left / right subtrees) before parent nodes
*/
// void	free_ast(t_ast *tree)
// {
// 	if (tree == NULL)
// 		return ;
// 	free_ast(tree->left);
// 	free_ast(tree->right);
// 	if (tree->file != NULL)
// 	{
// 		free(tree->file);
// 		tree->file = NULL;
// 	}
// 	if (tree->str != NULL)
// 	{
// 		free(tree->str);
// 		tree->str = NULL;
// 	}
// 	free(tree);
// }

void	free_ast(t_ast *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		free_ast(tree->left);
	if (tree->right != NULL)
		free_ast(tree->right);
	if (tree->file != NULL)
	{
		free(tree->file);
		tree->file = NULL;
	}
	if (tree->str != NULL)
	{
		free(tree->str);
		tree->str = NULL;
	}
	free(tree);
	tree = NULL;
}

void	clean_tools(t_tools *tools)
{
	if (tools->args != NULL)
	{
		free(tools->args);
		tools->args = NULL;
	}
	if (tools->tree != NULL)
		free_ast(tools->tree);
	if (tools->lexer_lst != NULL)
		clear_tokens(&tools->lexer_lst);
	tools->p_redir = NULL;
}
