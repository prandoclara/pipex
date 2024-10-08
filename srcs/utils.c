/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:02:00 by claprand          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:10 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(int code, char *message)
{
	ft_putstr_fd("pipex: ", 2);
	ft_fprintf(STDERR_FILENO, "%s\n", message);
	exit(code);
}

char	*get_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *av, char **env)
{
	char	*path;
	char	**allpaths;
	int		i;

	i = 0;
	if (get_env(env) == NULL)
		return (ft_strdup(av));
	allpaths = ft_split(get_env(env), ':');
	if (!allpaths)
		error_exit(EXIT_FAILURE, strerror(errno));
	path = ft_strdup(av);
	if (!path)
	{
		freetab(allpaths);
		error_exit(EXIT_FAILURE, strerror(errno));
	}
	while (access(path, F_OK | X_OK) != 0 && allpaths[i])
	{
		path = find_path(av, path, allpaths, i);
		i++;
	}
	freetab(allpaths);
	return (path);
}

char	*find_path(char *av, char *path, char **allpaths, int i)
{
	char	*tmp;

	tmp = NULL;
	if (path)
	{
		free(path);
		path = NULL;
	}
	tmp = ft_strjoin(allpaths[i], "/");
	if (!tmp)
		error_exit(EXIT_FAILURE, strerror(errno));
	path = ft_strjoin(tmp, av);
	if (!path)
		error_exit(EXIT_FAILURE, strerror(errno));
	free(tmp);
	return (path);
}
