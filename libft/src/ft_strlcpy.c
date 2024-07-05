/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:53:52 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 15:22:29 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size >= src_len + 1)
	{
		ft_memcpy(dst, src, src_len);
		dst[src_len] = 0;
	}
	else if (size)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}
// #include <stdio.h>
// #include <bsd/string.h> // also need to compile with -lbsd
// #include <assert.h>
//
// static int	g_test_i = 0;
//
// void	test_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	r_ft;
// 	size_t	r_org;
// 	char *dst_org = ft_strdup(dst);
//
// 	printf("[Test %i]\n", g_test_i);
// 	printf("The initial src is %s\n", src);
// 	printf("The initial dest is %s\n", dst);
// 	r_ft = ft_strlcpy(dst, src, size);
// 	r_org = strlcpy(dst_org, src, size);
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
// 	test_strlcpy(s_test, d_test, 12);
// 	char	s_test1[20] = "Hello";
// 	char	d_test1[0];
// 	test_strlcpy(s_test1, d_test1, 6);
// 	char	s_test2[0];
// 	char	d_test2[0];
// 	test_strlcpy(s_test2, d_test2, 0);
// 	char	s_test3[10] = "Bye ";
// 	char	d_test3[10] = "World!\0";
// 	test_strlcpy(s_test3, d_test3, 10); //truncate
// }
