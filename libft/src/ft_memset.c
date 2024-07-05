/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:52:18 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:26 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr_s;

	i = 0;
	ptr_s = s;
	while (i < n)
	{
		ptr_s[i] = c;
		i++;
	}
	return (ptr_s);
}
//
// #include <stdio.h>
// int	main(void)
// {
// 	char	s[20];
// 	char	s1[20];
//
// 	ft_memset(s, 'A', 10);
// 	memset(s1, 'A', 10);
// 	printf("Implementation: %s\n", s);
// 	printf("Original: %s\n", s1);
// 	return (1);
// }
