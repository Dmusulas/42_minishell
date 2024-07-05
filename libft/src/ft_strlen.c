/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:36:15 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/15 22:12:34 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}
// #include <assert.h>
// #include <string.h>
// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	if (argc == 2 && (strcmp(argv[1], "--auto") != 0))
// 	{
// 		printf("The string %s is of len %zu\n", argv[1], ft_strlen(argv[1]));
// 		assert(ft_strlen(argv[1]) == strlen(argv[1]));
// 		printf("Tests succeeded.");
// 	}
// 	else if (argc == 2 && (strcmp(argv[1], "--auto") == 0))
// 	{
// 		assert(ft_strlen("Testing.") == strlen("Testing."));
// 		assert(ft_strlen("") == strlen(""));
// 		assert(ft_strlen("See\0if\0null\0works") 
// 			== strlen("See\0if\0null\0works"));
// 		assert(ft_strlen("See\nif\nnewline\nworks") 
// 			== strlen("See\nif\nnewline\nworks"));
// 		printf("Tests succeeded.");
// 	}
// 	else
// 	{
// 	}
// 	return (1);
// }
