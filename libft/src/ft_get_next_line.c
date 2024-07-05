/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:37:35 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 21:51:26 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*readline(char *line, int fd)
{
	char	*buffer;
	ssize_t	bytes;
	char	*found;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	found = 0;
	while (!found)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		else if (bytes == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[bytes] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		found = ft_strchr_gnl(line, '\n');
	}
	free(buffer);
	return (line);
}

static char	*get_remainder(char *line)
{
	char	*next_line;
	char	*remainder;

	next_line = ft_strchr_gnl(line, '\n');
	if (!next_line++)
		return (NULL);
	remainder = ft_strdup_gnl(next_line);
	*next_line = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	line = readline(remainder, fd);
	remainder = get_remainder(line);
	return (line);
}
