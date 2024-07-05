/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:52 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/30 17:04:55 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_str_tolower(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > 64 && s[i] < 91)
			s[i] = ft_tolower(s[i]);
		i++;
	}
}

int	ft_convert_p(size_t c)
{
	char	*rtrn;
	int		len;

	len = 0;
	if (!c)
	{
		rtrn = ft_strdup("(nil)");
		len = 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		rtrn = generate_ll_base(c, 16);
		len = len + 2 + ft_strlen(rtrn);
		ft_str_tolower(rtrn);
	}
	ft_putstr_fd(rtrn, 1);
	free(rtrn);
	return (len);
}
