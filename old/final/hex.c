/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 23:26:01 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/21 23:44:30 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_size_ahead_hex(char *str, int i, char *base, int len_base)
{
	int	j;
	int	b;
	int	found;

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
	int	result;
	int	j;
	int	base_index;
	int	base_count;
	int	len_base;

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
	int		size;
	int		len_base;
	char	*base;

	base = "0123456789ABCDEF";
	len_base = 16;
	if (str[i] == '+')
		i++;
	if (str[i] != '0' || str[i + 1] != 'x')
		ft_perror("Invalid colour format\n");
	i += 2;
	size = check_size_ahead_hex(str, i, base, len_base);
	return (convert_to_int_hex(str, i, size, base));
}

int	contains_comma(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ',')
		return (i + 1);
	return (0);
}
