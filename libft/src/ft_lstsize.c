/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:54:52 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 15:43:30 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
// #include <stdio.h>
// int	main(void)
// {
// 	t_list *llist = ft_lstnew("world");
// 	ft_lstadd_front(&llist, ft_lstnew("Hello "));
// 	printf("Size of linked list, %i", ft_lstsize(llist));
// 	return (1);
// }
