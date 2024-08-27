/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:34:07 by dmusulas          #+#    #+#             */
/*   Updated: 2024/08/15 17:34:07 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * Displays an error message and terminates the program with a failure status.
 *
 * @param err The error message to be displayed.
 */
int	msg_error(char *err, t_exec *exec)
{
	perror(err);
	if (exec)
		free_exec(exec);
	return (EXIT_FAILURE);
}
