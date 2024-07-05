/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:04:28 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 19:08:29 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new_s = ft_calloc(sizeof(char), len + 1);
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s + start, len + 1);
	return (new_s);
}
//
// #include <stdio.h>
// void	test_substr(char const *s, unsigned int start, size_t len, int *i)
// {
// 	printf("Test %i: ft_substr(%s, %u, %zu)\n", *i, s, start, len);
// 	printf("\tNew string: %s\n", ft_substr(s, start, len));
// 	(*i)++;
// }
// int main(void)
// {
// 	int counter=0;
// 	test_substr("Hello World!", 6, 7, &counter);
// 	test_substr("Hello World!", 6, 0, &counter);
// 	test_substr("", 0, 0, &counter);
// 	test_substr("", 10, 10, &counter);
// 	test_substr("Too short", 5, 0, &counter);
// 	return (1);
// }
