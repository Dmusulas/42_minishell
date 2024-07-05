/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:08:01 by dmusulas          #+#    #+#             */
/*   Updated: 2024/01/28 19:47:48 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_u(unsigned int d)
{
	int		len;
	char	*ret;

	len = 0;
	ret = generate_num_base(d, 10);
	len = ft_strlen(ret);
	ft_putstr_fd(ret, 1);
	free(ret);
	return (len);
}
