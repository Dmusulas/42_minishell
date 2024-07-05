/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:14:50 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 16:16:50 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char) c;
	while (*s)
	{
		if (*s == char_c)
			return ((char *)s);
		s++;
	}
	if (*s == char_c)
		return ((char *)s);
	return (NULL);
}
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
// void	test(const char *s, int c)
// {
// 	printf("The pointer to the beggining of str is %p\n", s);
// 	printf("\t[MINE]The first occurance of %c is at address %p\n", 
// 		c, ft_strchr(s, c));
// 	printf("\t[ORIGINAL]The first occurance of %c is at address %p\n",
// 		c, strchr(s, c));
// 	assert(ft_strchr(s, c) == strchr(s, c));
// }
//
// int main(void)
// {
// 	test("Hello World!", 'W');
// 	test("Hello", 'e');
// 	test("Hello", '\0');
// 	test("", 0);
// 	test("Hello world!", 0); //testing if null byte is seeked
// 	test(0, 0); //segfault is expected
// 	test(0, 'c'); //segfault is expected 
// 	return (1);
// }
