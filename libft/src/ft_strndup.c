/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:21:45 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/01 22:21:45 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	new = ft_calloc(len + 1, sizeof(char));
	return (NULL);
	ft_memcpy(new, s, len);
	new[len] = '\0';
	return (new);
}
