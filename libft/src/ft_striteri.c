/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 11:08:22 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/18 11:30:25 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
//
// #include <stdio.h>
// void	crypt_42(unsigned int i, char *c)
// {
// 	i++;
// 	*c = 42;
// }
//
// int main(void)
// {
// 	char str[] = "Rnpu cebwrpg bs gur";
// 	ft_striteri(str, crypt_42);
// 	printf("%s", str);
// 	return (1);
// }
