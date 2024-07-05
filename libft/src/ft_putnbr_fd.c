/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:13:54 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/18 12:40:58 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + 0x30, fd);
	}
}
// #include <fcntl.h>
// int main(void)
// {
// 	int fd = open("test.txt", O_WRONLY | O_APPEND | O_CREAT, 0660);
//
// 	ft_putnbr_fd(1000, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(-1000, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(INT_MAX, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(0, fd);
// 	ft_putendl_fd("", fd);
// 	ft_putnbr_fd(INT_MIN, fd);
// 	ft_putendl_fd("", fd);
// 	return (1);
// }
