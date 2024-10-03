/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:45:15 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/03 17:45:16 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sorts a linked list in place using the provided comparison function.
 *
 * @param lst Pointer to the head of the list.
 * @param cmp Comparison function that returns a positive value if the
 * first argument is greater than the second, 0 if they are equal,
	and a negative value if the first argument is less than the second.
 */
void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *))
{
	t_list	*cur;
	void	*tmp;
	int		sorted;

	if (!lst || !*lst)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		cur = *lst;
		while (cur->next)
		{
			if (cmp(cur->content, cur->next->content) > 0)
			{
				tmp = cur->content;
				cur->content = cur->next->content;
				cur->next->content = tmp;
				sorted = 0;
			}
			cur = cur->next;
		}
	}
}
