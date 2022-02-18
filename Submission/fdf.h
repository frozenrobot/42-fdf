/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 10:05:03 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/22 00:18:40 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include "minilibx/include/mlx.h"
# include "fdf.h"
# include <math.h>

# define BUFFER_SIZE 32

typedef struct s_fdf
{
	int		height;
	int		width;
	int		***grid;
	void	*mlx_init_ptr;
	void	*mlx_new_win;
}			t_fdf;

typedef struct s_line
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	float	m;
	int		n;
}			t_line;

typedef struct s_points
{
	float	interval;
	float	start_x;
	float	start_y;
	int		i;
	int		j;
}			t_points;

typedef struct s_gnl
{
	int		ret;
	char	*line;
}			t_gnl;

int		ft_strlen(char *str);
int		contains_new_line(char *str);
void	*ft_memmove(void *dest, void *src, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*save_line(char *track);
char	*update_track(char *track, int i, int j);
int		free_buffer(char *buffer);
int		get_next_line(int fd, char **line);
int		check_size_ahead(char *str, int i);
int		ten_power(int exp);
int		convert_to_int(char *str, int i, int size);
int		ft_atoi(char *str);
void	mallocopy_points(t_points *points, int ***pixels, t_fdf *map);
void	rotate_points(t_points *points, int ***pixels, t_fdf *map);
void	elevate_points(t_points *points, int ***pixels, t_fdf *map);
int		***draw_points(t_fdf *map);
int		max_height(t_fdf *map);
void	ft_putchar(char c);
void	ft_perror(char *str);
void	ft_putstr(char *s);
char	*ft_strcpy(char *s, int i, char *tab, char c);
void	fill_grid_numbers(t_fdf *map, char *filename, int i, int j);
void	get_map(t_fdf *map, char *filename);
void	copy_grid(int **grid, int **copy, t_fdf *map);
int		find_height(char *filename);
int		find_width(char *filename);
int		check_size_ahead_hex(char *str, int i, char *base, int len_base);
int		power(int n, int exponent);
int		convert_to_int_hex(char *str, int i, int size, char *base);
int		get_hex(char *str, int i);
int		contains_comma(char *str);
void	draw_line_right(t_fdf *map, int ***pixels, int i, int j);
void	draw_line_down(t_fdf *map, int ***pixels, int i, int j);
void	draw_lines(t_fdf *map, int ***pixels);
int		deal_key(int key, t_fdf *map);
int		main(int argc, char *argv[]);
int		ft_getcolour(char *str);
int		count_words(char *s, char c);
char	**assign(char *s, char c, char **tab, int count);
char	**ft_split(char *s, char c);
void	free_map(t_fdf *map);
void	free_pixels(int ***pixels, t_fdf *map);
void	fill_grid_num_line(t_fdf *map);
t_gnl	gnl_sub(int fd);
int		count_words_free(char *s, char c);
void	change_n_dx(t_line *line);
void	change_n_dy(t_line *line);
float	MAX(float x, float y);
float	MIN(float x, float y);
float	MOD(float x);

#endif