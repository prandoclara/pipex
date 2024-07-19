/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:49:39 by claprand          #+#    #+#             */
/*   Updated: 2024/07/19 15:58:37 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char **p_cmd;
	char *path;

	p_cmd = ft_split(cmd, ' ');
	path = get_path(p_cmd[0], env);
	if (execve(path, p_cmd, env) == -1)
	{
		ft_putstr_fd("pipex : command not found: ", 2);
		ft_putendl_fd(p_cmd[0], 2);
		freetab(p_cmd);
		exit(0);
	}
}

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	close(fd);
	exec(av[2], env);
}

void	other_child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(fd);
	exec(av[3], env);
}

int main(int ac, char **av, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	pid_t	pid2;
	
	if (ac != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(-1);
	}
	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(-1);
	}
	if (pid == 0)
		child(av, p_fd, env);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(-1);
	}
	if (pid2 == 0)
		other_child(av, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}	