/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:15:58 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 17:40:12 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
