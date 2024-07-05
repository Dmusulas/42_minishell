/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:29:13 by dmusulas          #+#    #+#             */
/*   Updated: 2023/11/19 19:15:49 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_trim(char const *set, char c);
static char	*mega_strdup(char const *s1, int start, int end);

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (end <= 0)
		return (ft_strdup(""));
	while (char_to_trim(set, s1[start]))
		start++;
	while (char_to_trim(set, s1[end]))
		end--;
	return (mega_strdup(s1, start, end - (start - 1)));
}

static char	*mega_strdup(char const *s1, int start, int end)
{
	char	*new_str;

	if (start == (int) ft_strlen(s1) || end == 0)
		return (ft_strdup(""));
	new_str = ft_calloc(end + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str = ft_memcpy(new_str, s1 + start, end);
	return (new_str);
}

static int	char_to_trim(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

// #include <assert.h>
// #include <stdio.h>
// char *test_strtrim(const char *s1, const char *set, int *i)
// {
// 	char *new_str;
//
// 	new_str = ft_strtrim(s1, set);
// 	printf("[Test %i] ft_strtrim('%s', '%s')\n", *i, s1, set);
// 	printf("\tresult: '%s'\n", new_str);
// 	(*i)++;
// 	return (new_str);
// }
//
// int main(void)
// {
// 	int i = 0;
// 	char *t1 = test_strtrim("   Hello World!   ", " ", &i);
// 	free(t1);
// 	char *t2 = test_strtrim("-||- Hello World! -||- ", " -|", &i);
// 	free(t2);
// 	char *t3 = test_strtrim("-||- Hello World! -||- ", "", &i);
// 	free(t3);
// 	char *t4 = test_strtrim("", "", &i);
// 	free(t4);
// 	char *t5 = test_strtrim("abcdba", "acb", &i);
// 	free(t5);
// 	char *t6 = test_strtrim("  \t \t \n   \n\n\n\t", " \n\t", &i);
// 	free(t6);
// 	return (1);
// }
