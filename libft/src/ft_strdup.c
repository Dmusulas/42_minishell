/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:35:44 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/20 14:59:07 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;

	new = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s, ft_strlen(s) + 1);
	return (new);
}
// #include <assert.h>
// void	test_strdup(const char *s)
// {
// 	char	*original_r;
// 	char	*my_r;
//
// 	original_r = strdup(s);
// 	my_r = ft_strdup(s);
// 	assert(strcmp(my_r, original_r) == 0);
// }
// int main(void)
// {
// 	test_strdup("abc");
// 	test_strdup("");
// 	test_strdup((const char *) NULL);
// 	return 1;
// }
