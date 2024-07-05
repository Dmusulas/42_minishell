/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnumspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:14:50 by dmusulas          #+#    #+#             */
/*   Updated: 2024/02/20 22:42:45 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnumspace(const char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != ' ')
			return (0);
		s++;
	}
	return (1);
}
