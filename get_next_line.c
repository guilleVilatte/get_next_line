/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guill <guill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:00:00 by guill             #+#    #+#             */
/*   Updated: 2026/05/13 00:00:00 by guill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, const char *s2);
char	*extract_line(char **stash);

static int	read_and_append(int fd, char **stash, char *buffer)
{
	int	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	buffer[bytes] = '\0';
	if (bytes == 0)
		return (0);
	*stash = ft_strjoin(*stash, buffer);
	if (!*stash)
		return (-1);
	return (1);
}

static void	clean_stash(char **stash)
{
	free(*stash);
	*stash = NULL;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = extract_line(&stash);
	if (line)
		return (line);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (clean_stash(&stash), NULL);
	while (1)
	{
		ret = read_and_append(fd, &stash, buffer);
		if (ret < 0)
			return (free(buffer), clean_stash(&stash), NULL);
		line = extract_line(&stash);
		if (line)
			return (free(buffer), line);
		if (ret == 0)
		{
			free(buffer);
			if (stash && stash[0] != '\0')
			{
				line = stash;
				stash = NULL;
				return (line);
			}
			return (clean_stash(&stash), NULL);
		}
	}
}
