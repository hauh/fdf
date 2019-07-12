/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:06:02 by smorty            #+#    #+#             */
/*   Updated: 2019/07/12 23:46:10 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotation_matrix(t_fdf *m)
{
	m->matrix[X][X] = cos(m->angle[Y]) * cos(m->angle[Z]);
	m->matrix[X][Y] = cos(m->angle[Y]) * sin(m->angle[Z]);
	m->matrix[X][Z] = -sin(m->angle[Y]);
	m->matrix[Y][X] = sin(m->angle[X]) * sin(m->angle[Y]) * cos(m->angle[Z])
					- cos(m->angle[X]) * sin(m->angle[Z]);
	m->matrix[Y][Y] = sin(m->angle[X]) * sin(m->angle[Y]) * sin(m->angle[Z])
					+ cos(m->angle[X]) * cos(m->angle[Z]);
	m->matrix[Y][Z] = sin(m->angle[X]) * cos(m->angle[Y]);
	m->matrix[Z][X] = cos(m->angle[X]) * sin(m->angle[Y]) * cos(m->angle[Z])
					+ sin(m->angle[X]) * sin(m->angle[Z]);
	m->matrix[Z][Y] = cos(m->angle[X]) * sin(m->angle[Y]) * sin(m->angle[Z])
					- sin(m->angle[X]) * cos(m->angle[Z]);
	m->matrix[Z][Z] = cos(m->angle[X]) * cos(m->angle[Y]);
}

void	rotate(t_fdf *m, int key, int distance)
{
	if (key == 1 || key == 13)
		m->angle[X] += M_PI_4 / 8 * (key == 13 ? 1 : -1);
	else if (key == 12 || key == 14)
		m->angle[Y] += M_PI_4 / 8 * (key - 13);
	else if (key == 0 || key == 2)
		m->angle[Z] += M_PI_4 / 8 * (key - 1);
	else if (key < 0)
		m->angle[key + 3] += M_PI_4 / 64 * distance;
	else if (key == 34)
	{
		m->angle[X] = -asin(tan(M_PI_2 / 3.0));
		m->angle[Z] = M_PI_4;
	}
	rotation_matrix(m);
}