/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:36:35 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/30 12:46:07 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		ft_strlen2(char *str);
int		contains_new_line(char *str);
void	*ft_memmove(void *dest, void *src, int n);
char	*ft_strjoin(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
