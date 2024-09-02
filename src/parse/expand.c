/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:31:02 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 14:44:18 by clinggad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"
#include "minishell.h"

// TODO: merge file at home. remove this (added to libft already)
char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = '\0';
	return (new);
}

char	*expand_var(const char *s)
{

}
