/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 10:03:08 by kgulati           #+#    #+#             */
/*   Updated: 2021/06/30 12:51:40 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx2/include/mlx.h"
#include "fdf.h"
#include "libft1/libft.h"
#include "get_next_line/get_next_line.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
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
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			multiply *= -1;
		i++;
	}
	size = check_size_ahead(str, i);
	return (multiply * convert_to_int(str, i, size));
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
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

void fill_grid(t_fdf *map, char *filename)
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
			map->grid[i][j] = ft_atoi(row[j]);
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

	map->height = find_height(filename);
	map->width = find_width(filename);
	map->grid = (int **)malloc((map->height + 1) * sizeof(int *));
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = (int *)malloc((map->width + 1) * sizeof(int));
		i++;
	}
	fill_grid(map, filename);
}

void draw(float x, float y, float x1, float y1, t_fdf *map)
{
	float x_step = x1 - x;
	float y_step = y1 - y;
	int max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while (1)
	{
		mlx_pixel_put(map->mlx_init_ptr, map->mlx_new_win, x, y, 0xffffff);
		x += x_step;
		y += y_step;
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
	map->mlx_new_win = mlx_new_window(map->mlx_init_ptr, 1000, 1000, "fdf");


	draw(10, 10, 600, 300, map);
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
}