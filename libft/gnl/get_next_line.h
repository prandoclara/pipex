#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

size_t	ft_str_len(const char *s);
int		strchr_gnl(char *s, char x);
char	*ft_join_gnl(char *s1, char *s2);
void	clean_gnl(char *line, char *buffer);
char	*get_next_line(int fd);

#endif