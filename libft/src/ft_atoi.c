/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:05:35 by dmusulas          #+#    #+#             */
/*   Updated: 2024/02/22 16:07:16 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *nptr)
{
	long	nbr;
	int		i;
	int		sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+' || nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (nbr * sign);
}
// #include <stdio.h>
// #include <assert.h>
// #include <stdlib.h>
//
// void	test_ft_atoi(const char *nptr, int *counter)
// {
// 	printf("Test %d\n", *counter);
// 	printf("\t[MINE]Result is %i\n", ft_atoi(nptr));
// 	printf("\t[ORIGINAL]Result is %i\n", atoi(nptr));
// 	assert(ft_atoi(nptr) == atoi(nptr));
// 	(*counter)++;
// }
//
// int	main(void)
// {
// 	int	counter = 0;
//
// 	test_ft_atoi("0", &counter);
// 	test_ft_atoi("12312", &counter);
// 	test_ft_atoi("   12312", &counter);
// 	test_ft_atoi(" +12312", &counter);
// 	test_ft_atoi(" +-12312", &counter);
// 	test_ft_atoi("1231231232312", &counter);
// 	test_ft_atoi("123--+", &counter);
// 	test_ft_atoi("-100042", &counter);
// 	test_ft_atoi("-000010042", &counter);
// 	return (1);
// }
