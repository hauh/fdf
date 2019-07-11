/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:31:06 by smorty            #+#    #+#             */
/*   Updated: 2019/07/11 22:08:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		coord->x = (x + y) * 1.100;
		coord->y = (x - y) * -0.880 - coord->z0;
		coord = coord->right;
	}
	return (2);
}

void	rotation_matrix(t_fdf *m, t_dots *coord)
{
	m->vector[X][X] = cos(m->angle[Y]) * cos(m->angle[Z]);
	m->vector[X][Y] = -sin(m->angle[X]) * -sin(m->angle[Y]) * cos(m->angle[Z])
					+ (cos(m->angle[X]) * sin(m->angle[Z]));
	m->vector[X][Z] = -sin(m->angle[Y]) * cos(m->angle[X]) * cos(m->angle[Z])
					+ (sin(m->angle[Z]) * sin(m->angle[X]));
	m->vector[Y][X] = cos(m->angle[Y]) * -sin(m->angle[Z]);
	m->vector[Y][Y] = cos(m->angle[X]) * cos(m->angle[Z]) + (-sin(m->angle[X])
					* -sin(m->angle[Y]) * -sin(m->angle[Z]));
	m->vector[Y][Z] = sin(m->angle[X]) * cos(m->angle[Z]) + (-sin(m->angle[Z])
					* -sin(m->angle[Y]) * cos(m->angle[X]));
	m->vector[Z][X] = sin(m->angle[Y]);
	m->vector[Z][Y] = -sin(m->angle[X]) * cos(m->angle[Y]);
	m->vector[Z][Z] = cos(m->angle[X]) * cos(m->angle[Y]);
	while (coord)
	{
		coord->x = coord->x0 * m->vector[X][X] + coord->y0 * m->vector[Y][X]
					+ coord->z0 * m->vector[Z][X];
		coord->y = coord->x0 * m->vector[X][Y] + coord->y0 * m->vector[Y][Y]
					+ coord->z0 * m->vector[Z][Y];
		coord->z = coord->x0 * m->vector[X][Z] + coord->y0 * m->vector[Y][Z]
					+ coord->z0 * m->vector[Z][Z];
		coord = coord->right;
	}
}

/*
void	view_from_above(t_m *m)
{
	m->vector[X][X] = 1;
	m->vector[X][Y] = 0;
	m->vector[X][Z] = 0;
	m->vector[Y][X] = 0;
	m->vector[Y][Y] = 1;
	m->vector[Y][Z] = 0;
	m->vector[Z][X] = 0;
	m->vector[Z][Y] = 0;
	m->vector[Z][Z] = 1;
}

void	to_mirror_image(t_m *m)
{
	m->vector[X][X] = -1;
	m->vector[X][Y] = 0;
	m->vector[X][Z] = 0;
	m->vector[Y][X] = 0;
	m->vector[Y][Y] = -1;
	m->vector[Y][Z] = 0;
	m->vector[Z][X] = 0;
	m->vector[Z][Y] = 0;
	m->vector[Z][Z] = 1;
}*/