/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:26:38 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 15:39:57 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
//
// #include <stdio.h>
// void	test_lstnew(void *content)
// {
// 	t_list	*node;
// 	printf("With content %p: node was created to contain:\n", content);
// 	node = ft_lstnew(content);
// 	printf("\t content: %s | next: %p\n", (char *)node->content, node->next);
// }
// int main(void)
// {
// 	test_lstnew("testing");
// 	test_lstnew("");
// 	test_lstnew("Hello world!");
// 	return (1);
// }
