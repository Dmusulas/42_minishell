/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:45:35 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 13:50:53 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}
// #include <stdio.h>
// void	print_node(void	*content)
// {
// 	printf("%s->", (char *) content);
// }
// int	main(void)
// {
// 	t_list	*llist = NULL;
// 	t_list	*elem1 = ft_lstnew("Hello");
// 	t_list	*elem2 = ft_lstnew("World");
// 	t_list	*elem3 = ft_lstnew("!");
// 	ft_lstadd_back(&llist, elem1);
// 	ft_lstadd_back(&llist, elem2);
// 	ft_lstadd_back(&llist, elem3);
// 	ft_lstiter(llist, print_node);
// 	return (1);
// }
