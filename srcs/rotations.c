/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:31:06 by smorty            #+#    #+#             */
/*   Updated: 2019/07/10 22:44:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_dots *coord, double angle, int projection)
{
	double	y;
	double	z;
	double	cosinus;
	double	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	while (coord)
	{
		y = coord->y;
		z = coord->z;
		coord->y = y * cosinus + z * sinus;
		coord->z = -y * sinus + z * cosinus;
		coord = coord->right;
	}
	(void)projection;
}

void	rotate_y(t_dots *coord, double angle, int projection)
{
	double	x;
	double	z;
	double	cosinus;
	double	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	while (coord)
	{
		x = coord->x;
		z = coord->z;
		coord->x = x * cosinus + z * sinus;
		coord->z = -x * sinus + z * cosinus;
		coord = coord->right;
	}
	(void)projection;
}

void	rotate_z(t_dots *coord, double angle, int projection)
{
	double	x;
	double	y;
	double	cosinus;
	double	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	while (coord)
	{
		x = coord->x;
		y = coord->y;
		coord->x = x * cosinus - y * sinus;
		coord->y = x * sinus + y * cosinus;
		coord = coord->right;
	}
	(void)projection;
}

void	shift(t_dots *coord, int key)
{
	double	shift;

	shift = (key == 124 || key == 125 ? 1 : -1);
	if (key == 123 || key == 124)
		while (coord)
		{
			coord->x += shift;
			coord = coord->right;
		}
	else
		while (coord)
		{
			coord->y += shift;
			coord = coord->right;
		}
}

int		parallel(t_dots *coord)
{
	while (coord)
	{
		coord->x = (double)coord->x0;
		coord->y = (double)coord->y0;
		coord->z = (double)coord->z0;
		coord = coord->right;
	}
	return (1);
}

int		isometry(t_dots *coord)
{
	double x;
	double y;
	double cosinus;
	double sinus;

	cosinus = cos(0.523599);
	sinus = sin(0.523599);
	while (coord)
	{
		x = coord->x0;
		y = coord->y0;
		coord->x = (x - y) * cosinus;
		coord->y = (x + y) * sinus - coord->z0;
		coord = coord->right;
	}
	return (2);
}
