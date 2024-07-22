/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:49:39 by claprand          #+#    #+#             */
/*   Updated: 2024/07/22 12:12:34 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char **env)
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
		exit(-1);
	}
	if (execve(path, p_cmd, env) == -1)
	{
		freetab(p_cmd);
		free(path);
		error_exit(EXIT_FAILURE, strerror(errno));
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
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
	close(p_fd[1]);
	close(p_fd[0]);
	close(fd);
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
