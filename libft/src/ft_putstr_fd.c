/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:00:58 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/18 12:12:34 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
// #include <fcntl.h>
// int main(void)
// {
// 	int fd = open("test.txt", O_WRONLY | O_APPEND | O_CREAT, 0660);
// 	ft_putstr_fd("Hello World!", fd);
// 	close(fd);
// 	return (1);
// }
