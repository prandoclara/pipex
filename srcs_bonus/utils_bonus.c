/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:02:00 by claprand          #+#    #+#             */
/*   Updated: 2024/07/29 15:58:00 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	if_cmd_empty_or_space(char *av)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (av[0] == '\0')
	{
		ft_putstr_fd("pipex: permission denied:\n", 2);
		exit(EXIT_FAILURE);
	}
	while (av[i])
	{
		if (av[i] != ' ')
			n++;
		i++;
	}
	if (n == 0)
	{
		ft_putstr_fd("pipex: command not found:\n", 2);
		exit(EXIT_FAILURE);
	}
}

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
