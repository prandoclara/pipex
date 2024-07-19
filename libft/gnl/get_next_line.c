/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:06:31 by claprand          #+#    #+#             */
/*   Updated: 2024/06/12 10:10:34 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line_to_return(char *str)
{
	char	*final_line;
	int		i;

	final_line = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	final_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!final_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		final_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		final_line[i] = str[i];
		i++;
	}
	final_line[i] = '\0';
	return (final_line);
}

static char	*keep_what_is_left(char *str)
{
	int		i;
	int		j;
	char	*left_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}	
	left_str = (char *)malloc(sizeof(char) * (ft_str_len(str) - i + 1));
	if (!left_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		left_str[j++] = str[i++];
	left_str[j] = '\0';
	free (str);
	return (left_str);
}

static void	check_end_str(char **str)
{	
	if (*str[0] == '\0')
	{
		free(*str);
		*str = NULL;
	}
}

static char	*read_to_str(int fd, char *str)
{
	char	*buf;
	int		nbytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	nbytes = 1;
	while (nbytes != 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[nbytes] = '\0';
		str = ft_strjoin_gnl(str, buf);
		if (ft_str_chr(buf, '\n'))
			break ;
	}
	free(buf);
	check_end_str(&str);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_to_str(fd, str);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	line = get_line_to_return(str);
	if (!line)
	{
		free (str);
		return (NULL);
	}
	else
	{
		str = keep_what_is_left(str);
		return (line);
	}
	free(str);
	str = NULL;
	return (NULL);
}
