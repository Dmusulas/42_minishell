/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:51:17 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/16 16:29:58 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;
	size_t				i;

	cs1 = s1;
	cs2 = s2;
	i = 0;
	while (i < n)
	{
		if (*cs1 != *cs2)
		{
			return (*cs1 - *cs2);
		}
		cs1++;
		cs2++;
		i++;
	}
	return (0);
}
//
// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
//
// void	test_ft_memcmp(const void *s1, const void *s2, size_t n, int *counter)
// {
// 	int	result_original;
// 	int	result_mine;
//
// 	result_mine = ft_memcmp(s1, s2, n);
// 	result_original = memcmp(s1, s2, n);
// 	printf("Test %d\n", *counter);
// 	printf("\t[MINE] memcmp result: %d\n", result_mine);
// 	printf("\t[ORIGINAL] memcmp result: %d\n", result_original);
// 	assert(result_mine == result_original);
// 	(*counter)++;
// }
//
// int	main(void)
// {
// 	int counter = 0;
//
// 	// Test 1: Basic Test Case
// 	test_ft_memcmp("Hello, World!", "Hello, Universe!", 13, &counter);
//
// 	// Test 2: Compare Partial Strings
// 	test_ft_memcmp("Function", "Fun", 3, &counter);
//
// 	// Test 3: Compare Equal Strings
// 	test_ft_memcmp("Same", "Same", 4, &counter);
//
// 	// Test 4: Compare Arrays 
// 	test_ft_memcmp((int []){1, 2, 3, 4, 5}, 
// 		(int []){1, 2, 3, 4, 5}, 5 * sizeof(int), &counter);
// 	return (1);
// }
