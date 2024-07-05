/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 11:39:57 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/18 11:54:48 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}
// #include <fcntl.h>
// int main(void)
// {
// 	int fd = open("test.txt", O_WRONLY | O_APPEND);
// 	ft_putchar_fd('x', fd);
// 	close(fd);
// 	return (1);
// }
