/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:02:00 by claprand          #+#    #+#             */
/*   Updated: 2024/07/19 15:51:49 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int i;
	char **allpaths;
	char *path;
	char *exec;
	char **p_cmd;

	i = -1;
	allpaths = ft_split(get_env(env), ':');
	p_cmd = ft_split(cmd, ' ');
	if (!p_cmd)
	{
		freetab(allpaths);
		return (NULL);
	}
	while (allpaths[++i])
	{
		path = ft_strjoin(allpaths[i], "/");
		exec = ft_strjoin(path, p_cmd[0]);
		free(path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			freetab(p_cmd);
			return (exec);
		}
		free(exec);
	}
	freetab(allpaths);
	freetab(p_cmd);
	return (NULL);
}	
