/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:39:00 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 18:31:36 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char	*array = ft_calloc(10, sizeof(char));
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%i", array[i]);
// 	}
// 	printf("\n");
// 	char	*array2 = ft_calloc(0, sizeof(char));
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%i", array2[i]);
// 	}
// 	printf("\n");
// 	char	*array3 = ft_calloc(0, 0);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%i", array3[i]);
// 	}
// 	printf("\n");
// 	return (1);
// }
