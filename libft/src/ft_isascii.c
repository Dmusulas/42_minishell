/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:33:35 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/13 12:27:52 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <assert.h>

int	main(void)
{
	assert(ft_isascii('c') == 1);
	assert(ft_isascii('t') == 1);
	assert(ft_isascii(';') == 1);
	assert(ft_isascii('1') == 1);
	assert(ft_isascii(0x7F) == 1); // last char of 7-bit ascii
	assert(ft_isascii(0x00) == 1); // first char of 7-bit ascii
	assert(ft_isascii(0x8A) == 0); // outside 7-bit ascii
	return (1);
}
*/
