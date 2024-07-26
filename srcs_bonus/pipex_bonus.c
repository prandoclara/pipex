/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:49:39 by claprand          #+#    #+#             */
/*   Updated: 2024/07/26 13:07:11 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	execute(char *cmd, char **env)
{
	char	**p_cmd;
	char	*path;

	p_cmd = ft_split(cmd, ' ');
	if (!p_cmd)
		error_exit(EXIT_FAILURE, strerror(errno));
	path = get_path(p_cmd[0], env);
	if (access(path, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(p_cmd[0], 2);
		freetab(p_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
	if (execve(path, p_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(p_cmd[0], 2);
		freetab(p_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		error_exit(EXIT_FAILURE, strerror(errno));
	}
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fd);
	if_cmd_empty_or_space(av[2]);
	execute(av[2], env);
}

void	other_child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		close(p_fd[1]);
		close(p_fd[0]);
		error_exit(EXIT_FAILURE, strerror(errno));
	}
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	close(fd);
	if_cmd_empty_or_space(av[3]);
	execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (ac != 5)
		error_exit(EXIT_FAILURE, "./pipex infile cmd cmd outfile");
	if (pipe(p_fd) == -1)
		error_exit(EXIT_FAILURE, strerror(errno));
	pid = fork();
	if (pid == -1)
		error_exit(EXIT_FAILURE, strerror(errno));
	if (pid == 0)
		child(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
		error_exit(EXIT_FAILURE, strerror(errno));
	if (pid2 == 0)
		other_child(av, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
