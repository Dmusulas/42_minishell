/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:22 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/04 13:51:01 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return 0;

	return (ft_strcmp(cmd, "echo") == 0
			 || ft_strcmp(cmd, "cd") == 0
			 || ft_strcmp(cmd, "pwd") == 0
			 || ft_strcmp(cmd, "export") == 0
			 || ft_strcmp(cmd, "unset") == 0
			 || ft_strcmp(cmd, "env") == 0
			 || ft_strcmp(cmd, "exit") == 0);
}

t_ast	*ast_new(void)
{
	t_ast	*new_nd;

	new_nd = malloc(sizeof(t_ast));
	if (!new_nd)
	{
		perror("ast_new: malloc");
		return (NULL);
	}
	new_nd->lexer = NULL;
	new_nd->left = NULL;
	new_nd->right = NULL;
	new_nd->file = NULL;
	new_nd->b_cmd = false;
	return (new_nd);
}

int	parse_input(t_tools *tools)
{
	t_ast	*tree;

	tree = NULL;
	
	printf("LL inside parse start:\n");
	print_tokens(tools->lexer_lst);

	
	if (!tree)
		tree = parse_pipe(&tools->lexer_lst);
	else if (!tree)
		tree = parse_redir(&tools->lexer_lst);
	else if (!tree)
		tree = parse_cmd(&tools->lexer_lst);
	if (!tree)
		return (0);
	tools->tree = tree;

	printf("LL inside parse end:\n");
	print_tokens(tools->lexer_lst);

	return (1);
}
