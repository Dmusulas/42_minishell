/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:29:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 17:29:05 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void delete (void *content)
{
	char	*str;

	str = (char *)content;
	if (str == NULL)
		return ;
	str = NULL;
	free(str);
}

void	delete_duplicated_envp(t_tools *tools)
{
	ft_lstclear(&tools->envp, delete);
}
