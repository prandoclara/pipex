/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claprand <claprand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:36:19 by claprand          #+#    #+#             */
/*   Updated: 2024/07/19 15:42:56 by claprand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

# define STDIN 0
# define STDOUT 1

char	*get_env(char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	child(char **av, int *p_fd, char **env);
void	other_child(char **av, int *p_fd, char **env);

#endif