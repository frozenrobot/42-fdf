/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 22:13:01 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/22 01:07:08 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_right(t_fdf *map, int ***pixels, int i, int j)
{
	t_line	l;

	l.x = pixels[i][j][0];
	l.y = pixels[i][j][1];
	l.dx = pixels[i][j + 1][0] - pixels[i][j][0];
	l.dy = pixels[i][j + 1][1] - pixels[i][j][1];
	l.m = l.dy / l.dx;
	l.n = 0;
	if (MOD(l.m) < 1)
	{
		while (MOD(l.n) < MOD(l.dx))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, l.x + l.n, l.y
				+ (l.m * l.n), MIN(map->grid[i][j][1], map->grid[i][j + 1][1]));
			change_n_dx(&l);
		}
		return ;
	}
	while (MOD(l.n) < MOD(l.dy))
	{
		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, l.x + l.n / l.m,
			l.y + l.n, MIN(map->grid[i][j][1], map->grid[i][j + 1][1]));
		change_n_dy(&l);
	}
}

void	draw_line_down(t_fdf *map, int ***pixels, int i, int j)
{
	t_line	l;

	l.x = pixels[i][j][0];
	l.y = pixels[i][j][1];
	l.dx = pixels[i + 1][j][0] - pixels[i][j][0];
	l.dy = pixels[i + 1][j][1] - pixels[i][j][1];
	l.m = l.dy / l.dx;
	l.n = 0;
	if (MOD(l.m) < 1)
	{
		while (MOD(l.n) < MOD(l.dx))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, l.x + l.n, l.y
				+ (l.m * l.n), MIN(map->grid[i][j][1], map->grid[i + 1][j][1]));
			change_n_dx(&l);
		}
		return ;
	}
	while (MOD(l.n) < MOD(l.dy))
	{
		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, l.x + l.n / l.m,
			l.y + l.n, MIN(map->grid[i][j][1], map->grid[i + 1][j][1]));
		change_n_dy(&l);
	}
}

void	draw_lines(t_fdf *map, int ***pixels)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j + 1 < map->width)
				draw_line_right(map, pixels, i, j);
			if (i + 1 < map->height)
			{
				draw_line_down(map, pixels, i, j);
			}
			j++;
		}
		i++;
	}
}

int	deal_key(int key, t_fdf *map)
{
	(void) *map;
	if (key == 65307)
		exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	*map;
	int		***pixels;

	if (argc != 2)
	{
		ft_putstr("Usage: ./fdf filename\n");
		return (1);
	}
	map = (t_fdf *)malloc(sizeof(t_fdf));
	get_map(map, argv[1]);
	map->mlx_init_ptr = mlx_init();
	map->mlx_new_win = mlx_new_window(map->mlx_init_ptr, 500, 500, "fdf");
	pixels = draw_points(map);
	draw_lines(map, pixels);
	mlx_key_hook(map->mlx_new_win, deal_key, NULL);
	mlx_loop(map->mlx_init_ptr);
	free_pixels(pixels, map);
	free_map(map);
}
