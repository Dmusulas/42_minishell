/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:02:52 by dmusulas          #+#    #+#             */
/*   Updated: 2024/10/02 16:02:52 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Utility function to free memory allocated by splitting PATHs.
 *
 * @param array the 2d array to be freed
 */
void	free_2darray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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

void	fill_array(t_list *node, char **array, int *index)
{
	if (!node)
	{
		array[*index] = NULL;
		return ;
	}
	array[*index] = node->content;
	(*index)++;
	fill_array(node->next, array, index);
}

// Function to convert linked list to 2D array
char	**list_to_array(t_list *list)
{
	t_list	*current;
	int		count;
	int		index;
	char	**envp_array;

	current = list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp_array = malloc((count + 1) * sizeof(char *));
	if (!envp_array)
		return (NULL);
	index = 0;
	fill_array(list, envp_array, &index);
	return (envp_array);
}
