/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:41:15 by dmusulas          #+#    #+#             */
/*   Updated: 2024/02/21 19:39:08 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != 0 || *s2 != 0)
	{
		if (*s1 != *s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
//
// void	test(const char *s1, const char *s2, size_t n, int *counter)
// {
// 	printf("[Test %i] Comparing %s with %s for %zu bytes...\n", 
// 		*counter, s1, s2, n);
// 	printf("\t[FT_STRNCMP]Result is %i", ft_strncmp(s1, s2, n));
// 	printf("\t[STRNCMP]Result is %i", strncmp(s1, s2, n));
// 	assert(ft_strncmp(s1, s2, n) == strncmp(s1, s2, n));
// 	printf("\tAssertion against org is complete!");
// 	(*counter)++;
// }
//
// int	main(void)
// {
// 	int	test_counter;
//
// 	test_counter = 0;
// 	test("Hello", "Hello", 5, &test_counter);
// 	test("", "", 0, &test_counter);
// 	return (1);
// }
