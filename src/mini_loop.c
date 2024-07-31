/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:57:37 by clinggad          #+#    #+#             */
/*   Updated: 2024/07/31 14:56:26 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	mini_loop(t_tools *tools);

int	reset_loop(t_tools *tools)
{
	if(tools->args != NULL)
		free(tools->args);
	mini_loop(tools);
	return (1);
}

int	mini_loop(t_tools *tools)
{ 
	tools->args = readline("minishell$ ");
	if (tools->args == NULL)
	{
		ft_putendl_fd("Exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (tools->args[0] == '\0')
		return (reset_tools(tools));
	add_history(tools->args);
	reset_tools(tools);
	return (1);
}
