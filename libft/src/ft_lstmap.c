/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:29:26 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 15:27:31 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	tmp = lst;
	while (tmp)
	{
		new_node = ft_lstnew(f(tmp->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		tmp = tmp->next;
	}
	return (new_list);
}
// #include <stdio.h>
// void	*add_space(void *content)
// {
// 	char	*new_str;
//
// 	new_str = ft_strjoin(content, " ");
// 	return (new_str);
// }
//
// void	delete(void *content) {
// 	free(content);
// }
// void	print_node(void	*content)
// {
// 	printf("%s->", (char *) content);
// }
// int	main(void)
// {
// 	t_list	*llist = NULL;
// 	t_list	*elem1 = ft_lstnew(ft_strdup("Hello"));
// 	t_list	*elem2 = ft_lstnew(ft_strdup("World"));
// 	t_list	*elem3 = ft_lstnew(ft_strdup("!"));
// 	ft_lstadd_back(&llist, elem1);
// 	ft_lstadd_back(&llist, elem2);
// 	ft_lstadd_back(&llist, elem3);
// 	ft_lstiter(llist, &print_node);
// 	printf("\n");
// 	t_list	*new_list = ft_lstmap(llist, &add_space, &delete);
// 	ft_lstiter(new_list, print_node);
// 	ft_lstclear(&new_list, &delete);
// 	ft_lstclear(&llist, &delete);
// 	return (1);
// }
