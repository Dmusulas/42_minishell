/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:00:56 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/11 22:34:02 by pmolzer          ###   ########.fr       */
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
	// Save the current environment
	t_list *saved_env = tools->envp;

	// Clean other resources
	if (tools->args != NULL)
	{
		free(tools->args);
		tools->args = NULL;
	}
	if (tools->tree != NULL)
		free_ast(tools->tree);
	if (tools->lexer_lst != NULL)
		clear_tokens(&tools->lexer_lst);
	/* if (tools->envp != NULL)
		delete_duplicated_envp(tools); */
	tools->p_redir = NULL;

	// Restore the saved environment
	tools->envp = saved_env;
}