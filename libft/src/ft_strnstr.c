/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:17:55 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 16:31:06 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;

	little_len = ft_strlen(little);
	i = 0;
	if (little_len == 0)
		return ((char *)big);
	while (*big && i < len)
	{
		if (*big == *little && i + little_len <= len)
		{
			if (ft_strncmp(big, little, little_len) == 0)
				return ((char *)big);
		}
		big++;
		i++;
	}
	return (NULL);
}
// #include <stdio.h>
// #include <bsd/string.h>
// #include <assert.h>
//
// void	test_ft_strnstr(const char *big,
// 						const char *little, size_t len, int *counter)
// {
// 	printf("Test %d\n", *counter);
// 	printf("\t[MINE]Result is %p\n", ft_strnstr(big, little, len));
// 	printf("\t[ORIGINAL]Result is %p\n", strnstr(big, little, len));
// 	assert(ft_strnstr(big, little, len) == strnstr(big, little, len));
// }
//
// int	main(void)
// {
// 	int	counter = 0;
//
// 	test_ft_strnstr("Testing", "T", 7, &counter);
// 	test_ft_strnstr("Hello World!", "World", 20, &counter);
// 	test_ft_strnstr("Hello World!", "World", 0, &counter);
// 	test_ft_strnstr("Hello World!", "World", 7, &counter);
// 	test_ft_strnstr("Hello World!", "W", 7, &counter);
// 	test_ft_strnstr("Hello World!", "Hllo", 20, &counter);
// 	test_ft_strnstr("Hello World!", "World", 5, &counter);
// 	test_ft_strnstr("", "Hllo", 20, &counter);
// 	test_ft_strnstr("Hello", "", 20, &counter);
// 	return (1);
// }
