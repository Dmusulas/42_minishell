/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:33:14 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/03 17:33:14 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Traverses the linked list and returns the first node where
 * the content matches `val` according to the comparison function `cmp`.
 *
 * @param lst The list to traverse.
 * @param val The value to search for.
 * @param cmp The comparison function,
	which should return 0 when a match is found.
 * @return The pointer to the node where the match is found,
	or NULL if no match is found.
 */
t_list	*ft_lstfind_node(t_list *lst, void *val, int (*cmp)(void *, void *))
{
	t_list	*cur;

	cur = lst;
	while (cur)
	{
		if (cmp(cur->content, val) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
