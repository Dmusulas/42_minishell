/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:58:32 by clinggad          #+#    #+#             */
/*   Updated: 2024/08/30 15:59:30 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
