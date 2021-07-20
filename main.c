/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 10:03:08 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/20 21:01:13 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/include/mlx.h"
#include "fdf.h"
#include "libft1/libft.h"
#include "get_next_line/get_next_line.h"
#include <math.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_perror(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i]);
	exit(1);
}

static int	check_size_ahead(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] <= '9' && str[i + j] >= '0')
	{
		j++;
	}
	return (j);
}

static int	ten_power(int exp)
{
	if (exp == 0)
		return (1);
	return (10 * ten_power(exp - 1));
}

static int	convert_to_int(char *str, int i, int size)
{
	int	result;
	int	j;

	result = 0;
	j = 1;
	while (j <= size)
	{
		result += ((str[i] - '0') * ten_power(size - j));
		i++;
		j++;
	}
	return (result);
}

int	ft_atoi(char *str)
{
	int	i;
	int	multiply;
	int	size;

	if (!str)
		return (0);
	i = 0;
	multiply = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			multiply *= -1;
		i++;
	}
	size = check_size_ahead(str, i);
	if (size == 0)
		ft_perror("Invalid map format\n");
	return (multiply * convert_to_int(str, i, size));
}

int	check_size_ahead_hex(char *str, int i, char *base, int len_base)
{
	int j;
	int b;
	int found;

	j = 0;
	while (str[i + j])
	{
		b = 0;
		found = 0;
		while (b < len_base)
		{
			if (str[i + j] == base[b])
			{
				j++;
				found = 1;
			}
			b++;
		}
		if (found != 1)
			return (j);
	}
	return (j);
}

int	power(int n, int exponent)
{
	if (exponent < 0)
		return (0);
	else if (exponent == 0)
		return (1);
	else
		return (n * power(n, exponent - 1));
}

int	convert_to_int_hex(char *str, int i, int size, char *base)
{
	int result;
	int j;
	int base_index;
	int base_count;
	int len_base;

	len_base = 16;
	result = 0;
	j = 0;
	while (j <= size)
	{
		base_count = 0;
		while (base_count < len_base)
		{
			if (str[i + j] == base[base_count])
				base_index = base_count;
			base_count++;
		}
		result += (base_index * power(len_base, (size - 1 - j)));
		j++;
	}
	return (result);
}

int	get_hex(char *str, int i)
{
	int size;
	int len_base;
	char *base;

	base = "0123456789ABCDEF";
	len_base = 16;
	if (str[i] == '+')
		i++;
	if (str[i] != '0' || str[i + 1] != 'x')
		ft_perror("Invalid colour format");
	i += 2;
	size = check_size_ahead_hex(str, i, base, len_base);
	return (convert_to_int_hex(str, i, size, base));
}

int contains_comma(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		return (i + 1);
	return (0);
}

int ft_getcolour(char *str)
{
	if (!contains_comma(str))
		return (0xFFFFFF);
	return (get_hex(str, contains_comma(str)));
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	*ft_strcpy(char *s, int i, char *tab, char c)
{
	int	size;
	int	k;

	size = 0;
	while (s[i + size] != c && s[i + size] != '\0')
		size++;
	tab = malloc((size + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	k = 0;
	while (k < size && s[i + k] != '\0')
	{
		tab[k] = s[i + k];
		k++;
	}
	tab[k] = '\0';
	return (tab);
}

char	**assign(char *s, char c, char **tab, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < count && i < ft_strlen(s))
	{
		while (s[i] == c && i < ft_strlen(s))
			i++;
		tab[j] = ft_strcpy(s, i, tab[j], c);
		if (!tab[j])
		{
			while (j >= 0)
			{
				free(tab[j]);
				j--;
			}
			free(tab);
			return (NULL);
		}
		i += ft_strlen(tab[j]);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	tab = malloc((count + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = assign(s, c, tab, count);
	return (tab);
}

int find_height(char *filename)
{
	int fd;
	int height;
	char *line;

	height = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
		height++;
	close(fd);
	return (height);
}

int find_width(char *filename)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	return (count_words(line, ' '));
}

void fill_grid_numbers(t_fdf *map, char *filename)
{
	int i;
	int j;
	int fd;
	char *line;
	char **row;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		j = 0;
		row = ft_split(line, ' ');
		while (j < map->width)
		{
			map->grid[i][j][0] = ft_atoi(row[j]);
			free(row[j]);
			j++;
		}
		free(row);
		i++;
	}
}

void fill_grid_colours(t_fdf *map, char *filename)
{
	int i;
	int j;
	int fd;
	char *line;
	char **row;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		j = 0;
		row = ft_split(line, ' ');
		while (j < map->width)
		{
			map->grid[i][j][1] = ft_getcolour(row[j]);
			free(row[j]);
			j++;
		}
		free(row);
		i++;
	}
}

void get_map(t_fdf *map, char *filename)
{
	int i;
	int j;

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
	fill_grid_numbers(map, filename);
	fill_grid_colours(map, filename);
}

// void draw(float x, float y, float x1, float y1, t_fdf *map)
// {
// 	float x_step = x1 - x;
// 	float y_step = y1 - y;
// 	int max = MAX(MOD(x_step), MOD(y_step));
// 	x_step /= max;
// 	y_step /= max;
// 	while (1)
// 	{
// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x, y, 0xffffff);
// 		x += x_step;
// 		y += y_step;
// 	}
// }

void copy_grid(int **grid, int **copy, t_fdf *map)
{
	int i;
	int j;

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

int ***draw_points(t_fdf *map)
{
	float interval = (float)350 / (MAX(map->width, map->height) - 1);
	float start_x = (float)75;
	float start_y = 250 - (map->height - 1) * interval / 2;
	// printf("%f, %f, %f\n", interval, start_x, start_y);
	int ***pixels = (int ***)malloc((map->height) * sizeof(float **));
	int i = 0;
	int j;
	while (i < map->height)
	{
		pixels[i] = (int **)malloc((map->width) * sizeof(float *));
		j = 0;
		while (j < map->width)
		{
			pixels[i][j] = (int *)malloc(2 * sizeof(float));
			j++;
		}
		i++;
	}

	// copy_grid(map->grid, pixels, map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			// printf("Reached%i, %i\n", i, j);

			pixels[i][j][0] = start_x + j * interval;
			pixels[i][j][1] = start_y + i * interval;
			// printf("%d, %d\n", pixels[i][j][0], pixels[i][j][1]);
			j++;
		}
		i++;
	}
	// printf("Reached\n");
	//ROTATION (APPLY MATRIX)
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			pixels[i][j][0] -= 250;
			pixels[i][j][1] -= 250;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			pixels[i][j][0] = pixels[i][j][0] / sqrt(2) - pixels[i][j][1] / sqrt(2);
			pixels[i][j][1] = pixels[i][j][0] / sqrt(2) + pixels[i][j][1] / sqrt(2);
			j++;
		}
		i++;
	}
	
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			pixels[i][j][0] += 250;
			pixels[i][j][1] += 250;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j])
				pixels[i][j][1] -= *(map->grid[i][j]);
			// pixels[i][j][0] = 500 - pixels[i][j][0];
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, pixels[i][j][0], pixels[i][j][1], 0xffffff);
			j++;
		}
		i++;
	}

	return (pixels);
}

int max_height(t_fdf *map)
{
	int i;
	int j;
	int max;

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

void draw_line_right(t_fdf *map, int ***pixels, int i, int j)
{
	int x = pixels[i][j][0];
	int y = pixels[i][j][1];
	float dx = pixels[i][j + 1][0] - pixels[i][j][0];
	float dy = pixels[i][j + 1][1] - pixels[i][j][1];
	float m = dy / dx;
	int n = 0;
	// while (n < 5)
	// {
	// mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n, y + (int)(m * (float)x), 0xffffff);	n++;
	// }
	// if (MOD(m) > (float)1) //find x for each y
	// {
	// 	while (n <= (int)MOD(dy))
	// 	{
	// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)((float)n / m), y - n, 0xffffff);
	// 		n++;
	// 	}
	// }
	// else //y for each x
	// {
	// 	while (n <= (int)MOD(dx))
	// 	{
	// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n, y - (int)(m * (float)(x + n)), 0xffffff);
	// 		n++;
	// 	}
	// // }
	// if (MOD(m) > (float)1) //find x for each y
	// {
	// 	while (n <= (int)MOD(dy))
	// 	{
	// 		if (dy < 0)
	// 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x - (int)((float)n / (m)), y + n * (dy/MOD(dy)), 0xffffff);
	// 		n++;
	// 	}
	// }
	// else //y for each x
	// {
	// 	while (n <= (int)MOD(dx))
	// 	{
	// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n * dx/MOD(dx), y + (int)(m * (float)n), 0xffffff);
	// 		n++;
	// 	}
	// }
	// // if (MOD(m) > (float)1) //find x for each y
	// // {
	// // 	while (n <= (int)MOD(dy))
	// // 	{
	// // 		if (map->grid[i][j] || map->grid[i][j + 1])
	// // 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)(((float)n / MOD(m)) * dx/MOD(dx)), y + n * (dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// // 		else
	// // 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)(((float)n / MOD(m)) * dx/MOD(dx)), y + n * (dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// // 		n++;
	// // 	}
	// // }
	// // else //y for each x
	// // {
	// // 	while (n <= (int)MOD(dx))
	// // 	{
	// // 		if (map->grid[i][j] || map->grid[i][j + 1])
	// // 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n * dx/MOD(dx), y + (int)((MOD(m) * (float)n) * dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// // 		else
	// // 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n * dx/MOD(dx), y + (int)((MOD(m) * (float)n) * dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// // 		n++;
	// // 	}
	// }
	if (MOD(m) < 1)
	{
		while (MOD(n) < MOD(dx))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n, y + (m * n), MIN(map->grid[i][j][1], map->grid[i][j + 1][1]));
			if (dx > 0)
				n++;
			else
				n--;
		}
	}
	else
	{
		while (MOD(n) < MOD(dy))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n/m, y + n, MIN(map->grid[i][j][1], map->grid[i][j + 1][1]));
			if (dy > 0)
				n++;
			else
				n--;
		}
	}
}

void draw_line_down(t_fdf *map, int ***pixels, int i, int j)
{
	int x = pixels[i][j][0];
	int y = pixels[i][j][1];
	float dx = pixels[i + 1][j][0] - pixels[i][j][0];
	float dy = pixels[i + 1][j][1] - pixels[i][j][1];
	float m = dy / dx;
	int n = 0;
	// if (MOD(m) > (float)1) //find x for each y
	// {
	// 	while (n <= (int)dy)
	// 	{
	// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)((float)n / m), y + n, 0xffffff);
	// 		n++;
	// 	}
	// }
	// else // y for each x
	// {
	// 	while (n <= (int)dx)
	// 	{
	// 		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n, y + (int)(m * (float)x), 0xffffff);
	// 		n++;
	// 	}
	// }
	// if (MOD(m) > (float)1) //find x for each y
	// {
	// 	while (n <= (int)MOD(dy))
	// 	{
	// 		if (map->grid[i][j] || map->grid[i + 1][j])
	// 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)(((float)n / MOD(m)) * dx/MOD(dx)), y + n * (dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// 		else
	// 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + (int)(((float)n / MOD(m)) * dx/MOD(dx)), y + n * (dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// 		n++;
	// 	}
	// }
	// else //y for each x
	// {
	// 	while (n <= (int)MOD(dx))
	// 	{
	// 		if (map->grid[i][j] || map->grid[i + 1][j])
	// 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n * dx/MOD(dx), y + (int)((MOD(m) * (float)n) * dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// 		else
	// 			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n * dx/MOD(dx), y + (int)((MOD(m) * (float)n) * dy/MOD(dy)), 0xffffff - (*(map->grid[i][j])/max_height(map)) * (16776960));
	// 		n++;
	// 	}
	// }
	if (MOD(m) < 1)
	{
		while (MOD(n) < MOD(dx))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n, y + (m * n), MIN(map->grid[i][j][1], map->grid[i + 1][j][1]));
			if (dx > 0)
				n++;
			else
				n--;
		}
	}
	else
	{
		while (MOD(n) < MOD(dy))
		{
			mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x + n/m, y + n, MIN(map->grid[i][j][1], map->grid[i + 1][j][1]));
			if (dy > 0)
				n++;
			else
				n--;
		}
	}
}

void draw_lines(t_fdf *map, int ***pixels)
{
	int i;
	int j;

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
				// printf("reached");
			}
			j++;
		}
		i++;
	}
}

int deal_key(int key/*, void *map */)
{
	printf("%d", key);
	return (0);
}

int main(int argc, char *argv[])
{
	t_fdf *map;

	if (argc != 2)
	{
		ft_putstr("Usage: ./a.out filename\n");
		return (1);
	}
	map = (t_fdf *)malloc(sizeof(t_fdf));
	get_map(map, argv[1]);
	map->mlx_init_ptr = mlx_init();
	map->mlx_new_win = mlx_new_window(map->mlx_init_ptr, 500, 500, "fdf");

	int ***pixels =	draw_points(map);
	// draw_points(map);
	draw_lines(map, pixels);
	// draw(10, 10, 300, 300, map);
	// mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, 250, 250, 0xffffff);
	mlx_key_hook(map->mlx_new_win, deal_key, NULL);
	mlx_loop(map->mlx_init_ptr);
	// printf("%i\n", map->height);
	// printf("%i\n", map->width);
	// for (int i = 0; i < map->height; i++)
	// {
	// 	for (int j = 0; j < map->width; j++)
	// 	{
	// 		printf("%3i", map->grid[i][j]);
	// 	}
	// 	printf("\n");
	// }

	printf("%i\n", map->height);
	printf("%i\n", map->width);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%5i", map->grid[i][j][0]);
		}
		printf("\n");
	}
	printf("\n\n\n\n%i\n", map->height);
	printf("%i\n", map->width);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%10i", map->grid[i][j][1]);
		}
		printf("\n");
	}
}