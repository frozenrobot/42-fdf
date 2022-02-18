/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 22:37:45 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/21 23:16:24 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mallocopy_points(t_points *p, int ***pixels, t_fdf *map)
{
	p->i = 0;
	while (p->i < map->height)
	{
		pixels[p->i] = (int **)malloc((map->width) * sizeof(float *));
		p->j = 0;
		while (p->j < map->width)
		{
			pixels[p->i][p->j] = (int *)malloc(2 * sizeof(float));
			p->j++;
		}
		p->i++;
	}
	p->i = 0;
	while (p->i < map->height)
	{
		p->j = 0;
		while (p->j < map->width)
		{
			pixels[p->i][p->j][0] = p->start_x + p->j * p->interval;
			pixels[p->i][p->j][1] = p->start_y + p->i * p->interval;
			p->j++;
		}
		p->i++;
	}
}

void	rotate_points(t_points *points, int ***pixels, t_fdf *map)
{
	points->i = 0;
	while (points->i < map->height)
	{
		points->j = 0;
		while (points->j < map->width)
		{
			pixels[points->i][points->j][0] -= 250;
			pixels[points->i][points->j][1] -= 250;
			pixels[points->i][points->j][0] = pixels[points->i][points->j][0]
				/ sqrt(2) - pixels[points->i][points->j][1] / sqrt(2);
			pixels[points->i][points->j][1] = pixels[points->i][points->j][0]
				/ sqrt(2) + pixels[points->i][points->j][1] / sqrt(2);
			pixels[points->i][points->j][0] += 250;
			pixels[points->i][points->j][1] += 250;
			points->j++;
		}
		points->i++;
	}
}

void	elevate_points(t_points *p, int ***pixels, t_fdf *map)
{
	p->i = 0;
	while (p->i < map->height)
	{
		p->j = 0;
		while (p->j < map->width)
		{
			if (map->grid[p->i][p->j])
				pixels[p->i][p->j][1] -= *(map->grid[p->i][p->j]);
			p->j++;
		}
		p->i++;
	}
}

int	***draw_points(t_fdf *map)
{
	t_points	*points;
	int			***pixels;

	points = malloc(sizeof(t_points));
	points->interval = (float)350 / (MAX(map->width, map->height) - 1);
	points->start_x = (float)75;
	points->start_y = 250 - (map->height - 1) * points->interval / 2;
	pixels = (int ***)malloc((map->height) * sizeof(float **));
	mallocopy_points(points, pixels, map);
	rotate_points(points, pixels, map);
	elevate_points(points, pixels, map);
	free(points);
	return (pixels);
}

int	max_height(t_fdf *map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (i < map->height)
	{
		while (j < map->width)
		{
			if (map->grid[i][j][0] > max)
				max = map->grid[i][j][0];
			j++;
		}
		i++;
	}
	return (max);
}
