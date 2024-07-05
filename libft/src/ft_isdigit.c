/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:26:45 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/13 12:29:36 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 0x30 && c <= 0x39)
		return (1);
	else
		return (0);
}
// #include <assert.h>
//
// int	main(void)
// {
// 	assert(ft_isdigit('c') == 0);
// 	assert(ft_isdigit('t') == 0);
// 	assert(ft_isdigit(';') == 0);
// 	assert(ft_isdigit('1') == 1);
// 	assert(ft_isdigit('9') == 1);
// 	return (1);
// }
