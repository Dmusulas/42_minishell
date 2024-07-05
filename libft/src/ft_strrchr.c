/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:38:52 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 16:16:57 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	strl;
	char	char_c;

	strl = ft_strlen(s);
	char_c = (char) c;
	while (strl)
	{
		if (s[strl] == char_c)
			return ((char *)(&s[strl]));
		strl--;
	}
	if ((int)s[strl] == char_c)
		return ((char *)s);
	return (NULL);
}
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
// void	test(const char *s, int c, int *counter)
// {
// 	printf("[TEST %i] The pointer to the beggining of str is %p\n",*counter, s);
// 	printf("\t[MINE]The first occurance of %c is at address %p\n",
// 		c, ft_strrchr(s, c));
// 	printf("\t[ORIGINAL]The first occurance of %c is at address %p\n",
// 		c, strrchr(s, c));
// 	assert(ft_strrchr(s, c) == strchr(s, c));
// 	(*counter)++;
// }
//
// int main(void)
// {
// 	int	test_counter;
//
// 	test_counter = 0;
// 	test("Hello World!", 'W', &test_counter);
// 	test("", 0, &test_counter);
// 	test("Hello world!", 0, &test_counter); //testing if null byte is seeked
// 	test(0, 0, &test_counter); //segfault is expected
// 	test(0, 'c', &test_counter); //segfault is expected
// 	return (1);
// }
