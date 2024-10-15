/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:32:35 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/14 20:32:35 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "libft.h"

char	**parse_cmd_args(char *cmd_path, t_ast *node)
{
	int		arg_count;
	t_ast	*current;
	char	**args;

	arg_count = 1;
	current = node->right;
	while (current)
	{
		arg_count++;
		current = current->right;
	}
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	args[arg_count] = NULL;
	args[0] = ft_strdup(cmd_path);
	current = node->right;
	arg_count = 1;
	while (current != NULL)
	{
		args[arg_count] = ft_strdup(current->str);
		current = current->right;
		arg_count++;
	}
	return (args);
}

void	save_stdin_stdout(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
