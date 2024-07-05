/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:24:27 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 11:46:05 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*cs;
	unsigned char		cc;

	cs = s;
	cc = c;
	while (n--)
	{
		if (*cs == cc)
			return ((void *)cs);
		cs++;
	}
	return (NULL);
}
//
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
//
// void	test_ft_memchr(const void *s, int c, size_t n)
// {
// 	printf("The pointer to the beggining of str is %p\n", s);
// 	printf("\t[MINE]The first occurance of %c is at address %p\n",
// 		c, ft_memchr(s, c, n));
// 	printf("\t[ORIGINAL]The first occurance of %c is at address %p\n",
// 		c, memchr(s, c, n));
// 	assert(ft_memchr(s, c, n) == memchr(s, c, n));
// }
//
// int	main(void)
// {
// 	// Expected: Pointer to the 'W' in the string
// 	test_ft_memchr("Testing", 'X', 7);
// 	// Expected: NULL
// 	test_ft_memchr("Hello, World!", 'W', 13); 
// 	// Expected: Pointer to the 'I' at the end of the string
// 	test_ft_memchr("DucI", 'I', 6);
// 	// Expected: Pointer to the 'd' in the middle of the string
// 	test_ft_memchr("abcdef", 'd', 6);
// 	// Expected: NULL
// 	test_ft_memchr("", 'A', 0);
// 	// Expected: NULL
// 	test_ft_memchr("12345", '6', 3);
// 	// Expected: Pointer to the first null terminator
// 	test_ft_memchr("Hello\0World", '\0', 12);
// 	// Expected: NULL
// 	test_ft_memchr("Hello\0World", '\0', 5);
// 	// Expected: NULL
// 	test_ft_memchr("Test", -1, 4);
// 	return (1);
// }
