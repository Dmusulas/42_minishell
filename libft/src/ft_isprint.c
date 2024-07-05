/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:30:19 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/13 12:35:47 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 0x20 && c <= 0x7E)
		return (1);
	else
		return (0);
}
// #include <assert.h>
//
// int	main(void)
// {
// 	assert(ft_isprint('c') == 1);
// 	assert(ft_isprint('t') == 1);
// 	assert(ft_isprint(';') == 1);
// 	assert(ft_isprint('1') == 1);
// 	assert(ft_isprint('\t') == 0);
// 	assert(ft_isprint('\n') == 0);
// 	assert(ft_isprint(0x05) == 0);
// 	assert(ft_isprint('\f') == 0);
// 	return (1);
// }
