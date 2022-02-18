/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 23:19:56 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/22 01:51:44 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_grid_numbers(t_fdf *map, char *filename, int i, int j)
{
	int		fd;
	char	*line;
	char	**row;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		j = 0;
		row = ft_split(line, ' ');
		while (j < map->width && row[j])
		{
			map->grid[i][j][0] = ft_atoi(row[j]);
			map->grid[i][j][1] = ft_getcolour(row[j]);
			free(row[j]);
			j++;
		}
		free(line);
		free(row[j]);
		free(row);
		if (j != map->width)
			ft_perror("Invalid map format\n");
		i++;
	}
	free(line);
}

void	get_map(t_fdf *map, char *filename)
{
	int	i;
	int	j;

	map->height = find_height(filename);
	map->width = find_width(filename);
	map->grid = (int ***)malloc((map->height + 1) * sizeof(int *));
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = (int **)malloc((map->width) * sizeof(int *));
		j = 0;
		while (j < map->width)
		{
			map->grid[i][j] = (int *)malloc(2 * sizeof(int));
			j++;
		}
		i++;
	}
	fill_grid_numbers(map, filename, 0, 0);
}

void	copy_grid(int **grid, int **copy, t_fdf *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			copy[i][j] = grid[i][j];
			j++;
		}
		i++;
	}
}

int	find_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_perror("Invalid file\n");
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	free(line);
	close(fd);
	return (height);
}

int	find_width(char *filename)
{
	int		fd;
	char	*line;
	int		width;

	fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	width = count_words_free(line, ' ');
	while (get_next_line(fd, &line))
	{
		if (width != count_words_free(line, ' '))
			ft_perror("Invalid map format\n");
	}
	free(line);
	close(fd);
	return (width);
}
