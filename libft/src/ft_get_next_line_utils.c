/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:37:37 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 21:52:15 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;

	cdest = dest;
	csrc = src;
	if (dest == src || n == 0)
		return (dest);
	while (n--)
		*cdest++ = *csrc++;
	return (dest);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == char_c)
			return ((char *)s);
		s++;
	}
	if (*s == char_c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*new;
	size_t	len;

	if (!s || !*s)
		return (NULL);
	len = ft_strlen_gnl(s) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	ft_memcpy_gnl(new, s, len);
	return (new);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	size_t	total_len;
	size_t	s1_len;
	size_t	s2_len;
	char	*new_s;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	total_len = s1_len + s2_len + 1;
	new_s = malloc(sizeof(char) * total_len);
	if (!new_s)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_memcpy_gnl(new_s, s1, s1_len);
	ft_memcpy_gnl(new_s + s1_len, s2, s2_len + 1);
	if (s1)
		free(s1);
	return (new_s);
}
