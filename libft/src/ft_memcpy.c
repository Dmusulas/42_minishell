/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:46:16 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 16:00:09 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = dest;
	csrc = src;
	if (dest == src || n == 0)
		return (dest);
	while (n--)
		*cdest++ = *csrc++;
	return (dest);
}
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
// static int	g_test_n = 0;
// void	test_memcpy(void *dest, const void *src, size_t n)
// {
// 	char	*dest_ft;
// 	char	*dest_org;
//
// 	printf("[Test %i] Source string: %s\n", g_test_n, (char *) src);
// 	dest_ft = ft_memcpy(dest, src, n);
// 	dest_org = memcpy(dest, src, n);
// 	printf("\t[ft_memmove] Dest string: %s\n", dest_ft);
// 	printf("\t[memmove] Dest string: %s\n", dest_org);
// 	assert(ft_memcmp(dest_ft, dest_org, n) == 0);
// 	g_test_n++;
// }
// int	main(void)
// {
// 	char test[10];
// 	test_memcpy(test, ".....", 4);
// 	// test memory overwrite
// 	char test2[] = "abcde";
// 	char *test2_dst = test2;
// 	test_memcpy(test2 + 2, test2_dst, 3);
// 	// crashes
// 	test_memcpy(((void*)0), ((void*)0), 42);
// 	test_memcpy(((void *)0), "segufaultu pls", 14);
// 	test_memcpy("      ", ((void *) 0), 14);
// 	return (1);
// }
