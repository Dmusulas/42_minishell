/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clinggad <clinggad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:38:33 by clinggad          #+#    #+#             */
/*   Updated: 2024/09/02 16:33:38 by clinggad         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "lexer_parser.h"
#include "minishell.h"

/*
copy envp array to tools->envp
store in list? so we can modify and add content in between?
sort input
'export' built in -> prints list as
	'declare -x [..]'

*/

char	**ft_arrdup(char **arr)
{
	char	**dup;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		dup[i] = ft_strdup(arr[i]);
		if (dup[i] == NULL)
		{
			free_2darray(dup);
			return (dup);
		}
		i++;
	}
	return (dup);
}