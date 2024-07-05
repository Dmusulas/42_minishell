/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nums.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:45:26 by dmusulas          #+#    #+#             */
/*   Updated: 2023/12/04 16:03:47 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_base(unsigned int nbr, int base, char *rtrn,
							unsigned int count)
{
	unsigned int	quotient;
	unsigned int	remaindr;

	quotient = nbr;
	remaindr = 0;
	while (quotient != 0)
	{
		remaindr = quotient % base;
		if (remaindr < 10)
			rtrn[count - 1] = 48 + remaindr;
		else
			rtrn[count - 1] = 55 + remaindr;
		quotient = quotient / base;
		count--;
	}
	return (rtrn);
}

char	*generate_num_base(unsigned int num, int base)
{
	char			*rtrn;
	unsigned int	count;
	unsigned int	dup_num;

	count = 0;
	dup_num = num;
	if (num == 0)
		return (ft_strdup("0"));
	while (num != 0)
	{
		num /= base;
		count++;
	}
	rtrn = malloc(sizeof(char) * (count + 1));
	rtrn[count] = '\0';
	if (!rtrn)
		return (0);
	rtrn = convert_base(dup_num, base, rtrn, count);
	return (rtrn);
}

static char	*convert_ll_base(unsigned long long nbr, int base, char *rtrn,
							long long count)
{
	unsigned long long	quotient;
	unsigned long long	remaindr;

	quotient = nbr;
	remaindr = 0;
	while (quotient != 0)
	{
		remaindr = quotient % base;
		if (remaindr < 10)
			rtrn[count - 1] = 48 + remaindr;
		else
			rtrn[count - 1] = 55 + remaindr;
		quotient = quotient / base;
		count--;
	}
	return (rtrn);
}

char	*generate_ll_base(unsigned long long num, int base)
{
	char				*rtrn;
	unsigned long long	count;
	unsigned long long	dup_num;

	count = 0;
	dup_num = num;
	if (num == 0)
		return (ft_strdup("0"));
	while (num != 0)
	{
		num /= base;
		count++;
	}
	rtrn = malloc(sizeof(char) * (count + 1));
	rtrn[count] = '\0';
	if (!rtrn)
		return (0);
	rtrn = convert_ll_base(dup_num, base, rtrn, count);
	return (rtrn);
}
// #include <stdio.h>
// int main(void)
// {
// 	printf("Test: %s\n", generate_ll_base(11, 2));
// 	printf("Test: %s", generate_ll_base(11, 16));
// 	printf("Test: %s", generate_ll_base(11, 18));
// 	return EXIT_SUCCESS;
// }
