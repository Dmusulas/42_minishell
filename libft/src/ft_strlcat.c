/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:45 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 15:24:43 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i_src;
	size_t	i_dest;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i_dest = dstlen;
	i_src = 0;
	if (size == 0 || size <= dstlen)
		return (srclen + size);
	while (src[i_src] && i_src < size - dstlen - 1)
		dst[i_dest++] = src[i_src++];
	dst[i_dest] = '\0';
	return (srclen + dstlen);
}
// #include <stdio.h>
// #include <bsd/string.h> // also need to compile with -lbsd
// #include <assert.h>
//
// static int	g_test_i = 0;
//
// void	test_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	r_ft;
// 	size_t	r_org;
// 	char *dst_org = ft_strdup(dst);
//
// 	printf("[Test %i]\n", g_test_i);
// 	printf("The initial src is %s\n", src);
// 	printf("The initial dest is %s\n", dst);
// 	r_ft = ft_strlcat(dst, src, size);
// 	r_org = strlcat(dst_org, src, size);
// 	assert(r_ft == r_org);
// 	assert(strcmp(dst_org, dst) == 0);
// 	printf("[BSD] dst is %s\n", dst_org);
// 	printf("[ORG] dst is %s\n", dst);
// 	free(dst_org);
// 	printf("TEST SUCEEDED!\n");
// 	g_test_i++;
// }
//
//
// int main()
// {
// 	char	s_test[20] = "Hello";
// 	char	d_test[20] = "World!";
// 	test_strlcat(s_test, d_test, 12);
// 	char	s_test1[20] = "Hello";
// 	char	d_test1[0];
// 	test_strlcat(s_test1, d_test1, 6);
// 	char	s_test2[0];
// 	char	d_test2[0];
// 	test_strlcat(s_test2, d_test2, 0);
// 	char	s_test3[10] = "Bye ";
// 	char	d_test3[10] = "World!\0";
// 	test_strlcat(s_test3, d_test3, 10); //truncate
// }
