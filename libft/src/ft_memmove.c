/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:47:41 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 15:54:25 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = dest;
	csrc = src;
	if (dest == src || n == 0)
		return (dest);
	if (cdest < csrc)
	{
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		while (n--)
			cdest[n] = csrc[n];
	}
	return (dest);
}
// #include <string.h>
// #include <assert.h>
// #include <stdio.h>
//
// static int	g_test_n = 0;
// void	test_memmove(void *dest, const void *src, size_t n)
// {
// 	char	*dest_ft;
// 	char	*dest_org;
//
// 	printf("[Test %i] Source string: %s\n", g_test_n, (char *) src);
// 	dest_ft = ft_memmove(dest, src, n);
// 	dest_org = memmove(dest, src, n);
// 	printf("\t[ft_memmove] Dest string: %s\n", dest_ft);
// 	printf("\t[memmove] Dest string: %s\n", dest_org);
// 	assert(ft_memcmp(dest_ft, dest_org, n) == 0);
// 	g_test_n++;
// }
// int main(void)
// {
// 	char test[10];
// 	test_memmove(test, ".....", 4);
// 	char test2[] = "abcde";
// 	char *test2_dst = test2;
// 	test_memmove(test2, test2_dst, 2);
// 	//crashes
// 	test_memmove(test, ((void*)0), 42);
// 	test_memmove(((void*)0), test, 42);
// 	test_memmove(((void*)0), ((void*)0), 42);
// 	return (1);
// }
