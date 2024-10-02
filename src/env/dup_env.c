/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:12:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 17:12:32 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	duplicate_env(t_tools *tools)
{
	t_list	*envp_l;
	t_list	*new_node;
	int		i;

	envp_l = ft_lstnew(tools->envp_org[0]);
	if (!envp_l)
		return (0);
	i = 1;
	while (tools->envp_org[i])
	{
		new_node = ft_lstnew(tools->envp_org[i]);
		if (!new_node)
			return (0);
		ft_lstadd_back(&envp_l, new_node);
		i++;
	}
	tools->envp = envp_l;
	return (1);
}
