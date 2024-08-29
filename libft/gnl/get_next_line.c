/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:06:31 by claprand          #+#    #+#             */
/*   Updated: 2024/08/29 10:15:07 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_str_len(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	strchr_gnl(char *s, char x)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == x)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	join = malloc(ft_str_len(s1) + ft_str_len(s2) + 1);
	if (!join)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = 0;
	free(s1);
	return (join);
}

void	clean_gnl(char *line, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != 10)
		i++;
	if (line[i] == 10)
		i++;
	while (line[i])
	{
		buffer[j] = line[i];
		line[i] = 0;
		i++;
		j++;
	}
	buffer[j] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = 0;
	line = ft_join_gnl(line, buffer);
	byte_read = 1;
	while (byte_read > 0 && !strchr_gnl(line, 10))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(line), NULL);
		buffer[byte_read] = 0;
		line = ft_join_gnl(line, buffer);
	}
	if (!line[0])
		return (free(line), NULL);
	else
		clean_gnl(line, buffer);
	return (line);
}
