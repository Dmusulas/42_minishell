/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:12:32 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/11 16:31:49 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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
 * Find an environment variable in the linked list and update it if found.
 * If not found, add a new node with the new variable and value.
 * After adding, the list is sorted alphabetically.
 *
 * @param lst Pointer to the head of the environment list.
 * @param new_envp New environment variable string (e.g., "EX=y").
 * @return 1 if the value was updated, 0 if a new node was added, or -1 if
 * memory allocation fails.
 */
int	update_or_add_envp(t_list **lst, const char *new_envp)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*new_node;

	cur = *lst;
	prev = NULL;
	printf("[DEBUG] Updating or adding: %s\n", new_envp);
	while (cur)
	{
		printf("[DEBUG] Comparing with: %s\n", (char *)cur->content);
		if (!cmp_envp(cur->content, (void *)new_envp))
		{
			printf("[DEBUG] Found existing variable, updating\n");
			cur->content = (void *)new_envp;
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	printf("[DEBUG] Variable not found, adding new node\n");
	new_node = ft_lstnew((void *)ft_strdup(new_envp));
	if (!new_node)
	{
		printf("[DEBUG] Failed to create new node\n");
		return (-1);
	}
	if (prev)
		prev->next = new_node;
	else
		*lst = new_node;
	ft_lstsort(lst, cmp_envp);
	printf("[DEBUG] New node added and list sorted\n");
	return (1);
}
