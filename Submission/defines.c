/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 00:09:15 by kgulati           #+#    #+#             */
/*   Updated: 2021/07/22 00:12:13 by kgulati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	MAX(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

float	MIN(float x, float y)
{
	if (x < y)
		return (x);
	return (y);
}

float	MOD(float x)
{
	if (x > 0)
		return (x);
	return (x * (-1));
}
