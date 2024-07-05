/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:28:52 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/15 18:38:45 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c);
int	ft_isalpha(int c);

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
/*
#include <assert.h>

int	main(void)
{
	assert(ft_isalnum('c') == 1);
	assert(ft_isalnum('1') == 1);
	assert(ft_isalnum(';') == 0);
	assert(ft_isalnum('!') == 0);
	return (1);
}
*/
