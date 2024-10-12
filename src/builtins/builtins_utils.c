/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:07:03 by pmolzer           #+#    #+#             */
/*   Updated: 2024/10/12 14:10:47 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_list **envp, const char *var_name)
{
	t_list	*prev;
	t_list	*current;
	char	*env_var;
	size_t	var_len;

	prev = NULL;
	current = *envp;
	var_len = ft_strlen(var_name);
	while (current)
	{
		env_var = (char *)current->content;
		if (ft_strncmp(env_var, var_name,
				var_len) == 0 && env_var[var_len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
