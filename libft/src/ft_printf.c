/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:50:51 by dmusulas          #+#    #+#             */
/*   Updated: 2024/01/28 19:46:16 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_convert(const char *s, va_list arg)
{
	s++;
	if (*s == 'c')
		return (ft_convert_c(va_arg(arg, int)));
	else if (*s == 's')
		return (ft_convert_s(va_arg(arg, char *)));
	else if (*s == 'p')
		return (ft_convert_p(va_arg(arg, unsigned long)));
	else if (*s == 'u')
		return (ft_convert_u(va_arg(arg, unsigned int)));
	else if (*s == 'd' || *s == 'i')
		return (ft_convert_d(va_arg(arg, int)));
	else if (*s == 'l')
		return (ft_convert_ll(va_arg(arg, long long)));
	else if (*s == 'x')
		return (ft_convert_x(va_arg(arg, int), 0));
	else if (*s == 'X')
		return (ft_convert_x(va_arg(arg, int), 1));
	else if (*s == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		len;

	if (!s)
		return (-1);
	va_start(args, s);
	len = 0;
	while (*s)
	{
		if (*s == '%')
			len += ft_convert(s++, args);
		else
		{
			ft_putchar_fd(*s, 1);
			len++;
		}
		s++;
	}
	va_end(args);
	return (len);
}
