/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:22:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/01 22:22:32 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int err_type, t_tools *tools)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err_type == ERR_LEX)
		ft_putstr_fd("Error processing input\n", STDERR_FILENO);
	else if (err_type == ERR_QUO)
		ft_putstr_fd("Invalid quote count\n", STDERR_FILENO);
	else if (err_type == ERR_PAR)
		ft_putstr_fd("Error parsing input\n", STDERR_FILENO);
	reset_tools(tools);
	return (EXIT_FAILURE);
}
