/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:09:32 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 13:21:30 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	new_s = malloc(sizeof(char) * total_len);
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s1, s1_len);
	ft_memcpy(new_s + s1_len, s2, s2_len + 1);
	return (new_s);
}
//
// #include <stdio.h>
//
// void	test_strjoin(char const *s1, char const *s2, int *i)
// {
// 	printf("Test %i: ft_strjoin(%s, %s)\n", *i, s1, s2);
// 	printf("\tNew string: %s\n", ft_strjoin(s1, s2));
// 	(*i)++;
// }
// int main(void)
// {
// 	int counter = 0;
//
// 	test_strjoin("Hello", " World!", &counter);
// 	test_strjoin("", " World!", &counter);
// 	test_strjoin("", "", &counter);
// 	test_strjoin("Hello", "", &counter);
// 	return (1);
// }
