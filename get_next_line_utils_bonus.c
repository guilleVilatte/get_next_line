/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvilatt <guvilatt@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:16:36 by guvilatt          #+#    #+#             */
/*   Updated: 2026/05/22 16:16:40 by guvilatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
static char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
*/
static char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s2)
		return (s1);
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (free(s1), NULL);
	i = -1;
	while (s1 && s1[++i])
		result[i] = s1[i];
	free(s1);
	i = -1;
	while (s2[++i])
		result[len1 + i] = s2[i];
	result[len1 + len2] = '\0';
	return (result);
}

char	*extract_line(char **stash)
{
	int		i;
	char	*line;
	char	*temp;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if (!(*stash)[i])
		return (NULL);
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while ((*stash)[++i] != '\n')
		line[i] = (*stash)[i];
	line[i] = '\n';
	line[i + 1] = '\0';
	temp = ft_strdup(*stash + i + 1);
	free(*stash);
	*stash = temp;
	return (line);
}
