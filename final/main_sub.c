/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 23:39:43 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/22 00:14:43 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_n_dx(t_line *line)
{
	if (line->dx > 0)
		line->n++;
	else
		line->n--;
}

void	change_n_dy(t_line *line)
{
	if (line->dy > 0)
		line->n++;
	else
		line->n--;
}

void	free_pixels(int ***pixels, t_fdf *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			free(&pixels[i][j][0]);
			free(&pixels[i][j][1]);
			free(pixels[i][j]);
			j++;
		}
		free(pixels[i]);
		i++;
	}
	free(pixels);
}

void	free_map(t_fdf *map)
{
	int	i;
	int	j;

	i = 0;
	while (i <= map->height)
	{
		j = 0;
		while (j < map->width)
		{
			free(&map->grid[i][j][0]);
			free(&map->grid[i][j][1]);
			free(map->grid[i][j]);
			j++;
		}
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}
