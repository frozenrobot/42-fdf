/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 10:05:03 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/20 21:00:54 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>

# define MAX(x, y) ((x > y) ? x : y)
# define MIN(x, y) ((x > y) ? y : x)
# define MOD(x) ((x < 0) ? -x : x)

typedef struct s_fdf
{
	int height;
	int width;
	int ***grid;
	void *mlx_init_ptr;
	void *mlx_new_win;
}			t_fdf;
 
#endif