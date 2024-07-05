/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:01:00 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/13 12:17:55 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 0x41 && c <= 0x5A) || (c >= 0x61 && c <= 0x7A))
	{
		return (1);
	}
	return (0);
}
/*
#include <assert.h>

int	main(void)
{
	assert(ft_isalpha('c') == 1);
	assert(ft_isalpha('t') == 1);
	assert(ft_isalpha(';') == 0);
	assert(ft_isalpha('1') == 0);
	return (1);
}
*/
