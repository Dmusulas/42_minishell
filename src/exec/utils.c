/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:35:35 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:35:35 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * Initiates exec struct. Argc - 3 is simply:
 * argument count - program_name (i = 0) - infile (i = 1) - outfile (i = argc)
 *
 * @param argc is the argument count
 * @return a pointer to newly created struct
 */
t_exec	*init_exec(int argc)
{
	t_exec	*exec;

	exec = malloc(1 * sizeof(t_exec));
	if (!exec)
		msg_error(ERR_MALLOC, exec);
	exec->cmd_count = argc;
	exec->cmd_start_position = 0;
	exec->here_doc = false;
	exec->is_invalid_infile = false;
	exec->cmd_paths = NULL;
	exec->cmd_args = NULL;
	exec->in_fd = STDIN_FILENO;
	exec->out_fd = STDOUT_FILENO;
	return (exec);
}

/**
 * Frees exec structure
 *
 * @param exec pointer to exec object to free
 */
void	free_exec(t_exec *exec)
{
	int	i;
	int	j;

	if (exec->cmd_paths)
		free_2darray(exec->cmd_paths);
	if (exec->cmd_args)
	{
		i = 0;
		while (exec->cmd_args[i])
		{
			j = 0;
			while (exec->cmd_args[i][j])
			{
				free(exec->cmd_args[i][j]);
				j++;
			}
			free(exec->cmd_args[i]);
			i++;
		}
		free(exec->cmd_args);
	}
	close(exec->in_fd);
	close(exec->out_fd);
	free(exec);
}

/**
 * Utility function to free memory allocated by splitting PATHs.
 *
 * @param array the 2d array to be freed
 */
void	free_2darray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
