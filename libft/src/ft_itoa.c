/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:50:24 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/18 00:20:04 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_len(int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = count_len(nbr);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	else if (nbr == 0)
		str[0] = '0';
	while (len && nbr != 0)
	{
		str[len - 1] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	return (str);
}

static int	count_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}
// #include <limits.h>
// #include <stdio.h>
// void	test_count_len(int n)
// {
// 	printf("The number %i has %i chars\n", n, count_len(n));
// }
//
// void	test_ft_itoa(int n)
// {
// 	printf("The number %i has been converted to %s\n", n, ft_itoa(n));
// }
//
// int main(void)
// {
// 	test_count_len(1231);
// 	test_count_len(-1231);
// 	test_count_len(INT_MAX);
// 	test_count_len(INT_MIN);
// 	test_count_len(1231);
// 	test_ft_itoa(1231);
// 	test_ft_itoa(-1231);
// 	test_ft_itoa(1231);
// 	test_ft_itoa(0);
// 	test_ft_itoa(INT_MIN);
// 	test_ft_itoa(INT_MAX);
// 	return (1);
// }
