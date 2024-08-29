/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:12:38 by claprand          #+#    #+#             */
/*   Updated: 2024/08/29 10:14:24 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# include <string.h>
# include <errno.h>

char	*get_env(char **env);
char	*get_path(char *cmd, char **env);
int		execute(char *cmd, char **env);
void	error_exit(int code, char *message);
char	*find_path(char *av, char *path, char **paths, int i);
void	if_cmd_empty_or_space(char *av);
void	get_here_doc_lines(char **av, int *p_fd);
void	get_here_doc(char **av);
void	do_pipe(char *p_cmd, char **env);

#endif