/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:49:39 by claprand          #+#    #+#             */
/*   Updated: 2024/08/29 11:24:35 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	get_here_doc_lines(char **av, int *p_fd)
{
	char	*line;

	close(p_fd[0]);
	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
}

void	get_here_doc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
		get_here_doc_lines(av, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

void	do_pipe(char *p_cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		error_exit(EXIT_FAILURE, strerror(errno));
	pid = fork();
	if (pid == -1)
		error_exit(EXIT_FAILURE, strerror(errno));
	if (pid == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		if_cmd_empty_or_space(p_cmd);
		execute(p_cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		p_fd[2];

	if (ac < 5)
		error_exit(EXIT_FAILURE, "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2");
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			error_exit(EXIT_FAILURE, "./pipex here_doc LIMITER cmd cmd1 file");
		i = 3;
		p_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		get_here_doc(av);
	}
	else
	{
		i = 2;
		p_fd[0] = open(av[1], O_RDONLY);
		p_fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(p_fd[0], STDIN_FILENO);
	}
	while (i < ac - 2)
		do_pipe(av[i++], env);
	dup2(p_fd[1], STDOUT_FILENO);
	if_cmd_empty_or_space(av[ac - 2]);
	execute(av[ac - 2], env);
}
