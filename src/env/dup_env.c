/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:12:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/11/06 16:39:09 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

/**
 * Duplicates the environment variables from tools->envp_org into a linked list.
 *
 * @param tools Pointer to a tools structure that contains the original envp.
 * @return 1 if successful, 0 if memory allocation fails.
 */
int	duplicate_env(t_tools *tools)
{
	t_list	*envp_l;
	t_list	*new_node;
	int		i;
	char	*content;

	envp_l = ft_lstnew(tools->envp_org[0]);
	if (!envp_l)
		return (0);
	i = 1;
	while (tools->envp_org[i])
	{
		content = ft_strdup(tools->envp_org[i]);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (0);
		ft_lstadd_back(&envp_l, new_node);
		i++;
	}
	tools->envp = envp_l;
	return (1);
}

/**
 * Compare two environment variable strings based on their key (before '=').
 *
 * @param a Pointer to the first environment variable string.
 * @param b Pointer to the second environment variable string.
 * @return A negative, 0, or positive value based on lexicographical comparison.
 */
int	cmp_envp(void *a, void *b)
{
	char	*env1;
	char	*env2;
	char	*key1;
	char	*key2;

	env1 = (char *)a;
	env2 = (char *)b;
	key1 = ft_strchr(env1, '=');
	key2 = ft_strchr(env2, '=');
	if (!key1 || !key2)
		return (0);
	return (ft_strncmp(env1, env2, (size_t)(key1 - env1)));
}

/**
 * Updates an existing environment variable in the linked list if it is found.
 * If the variable does not exist, a new node is created and added to the list.
 * The function first locates the '=' character to determine the variable name,
 * then checks for an existing variable with the same name. If found, it updates
 * the variable's value; if not, it adds the new variable to the end of the list.
 * 
 * @param lst Pointer to the head of the environment list.
 * @param new_envp New environment variable string (e.g., "EX=y").
 * @return 1 if the value was updated, 0 if a new node was added, or -1 if
 * memory allocation fails.
 */
int	update_or_add_envp(t_list **lst, const char *new_envp)
{
	t_list	*cur;
	char	*equal_sign;
	size_t	var_len;
	char	*new_content;

	// Find the '=' in the new environment variable
	equal_sign = ft_strchr(new_envp, '=');
	if (!equal_sign)
		return (EXIT_FAILURE);
	
	// Calculate length of variable name (before '=')
	var_len = equal_sign - new_envp;
	
	// Create a copy of the new environment variable
	new_content = ft_strdup(new_envp);
	if (!new_content)
		return (-1);

	// Look for existing variable
	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->content, new_envp, var_len) == 0 
			&& ((char *)cur->content)[var_len] == '=')
		{
			// Found matching variable, update it
			free(cur->content);
			cur->content = new_content;
			return (EXIT_SUCCESS);
		}
		cur = cur->next;
	}

	// Variable not found, add new node
	cur = ft_lstnew(new_content);
	if (!cur)
	{
		free(new_content);
		return (-1);
	}
	ft_lstadd_back(lst, cur);
	return (EXIT_SUCCESS);
}
