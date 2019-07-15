/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:35:28 by smorty            #+#    #+#             */
/*   Updated: 2019/07/15 23:40:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_matrix(t_dots *coord, double matrix[4][4])
{
	while (coord)
	{
		coord->x = coord->x0 * matrix[X][X] * matrix[S][X]
				+ coord->y0 * matrix[X][Y] * matrix[S][Y]
				+ coord->z0 * matrix[X][Z] * matrix[S][Z];
		coord->x *= matrix[S][S];
		coord->x += matrix[X][S];
		coord->y = coord->x0 * matrix[Y][X] * matrix[S][X]
				+ coord->y0 * matrix[Y][Y] * matrix[S][Y]
				+ coord->z0 * matrix[Y][Z] * matrix[S][Z];
		coord->y *= matrix[S][S];
		coord->y += matrix[Y][S];
		coord = coord->right;
	}
}

void	key_press(int key, t_fdf *m)
{
	if (key == 53)
		exit(0);
	else if (key == 48)
		m->tab_pressed = ~m->tab_pressed;
	else if ((key >= 0 && key <= 2) || (key >= 12 && key <= 14) || key == 34)
		rotate(m, key, 0);
	else if (key >= 123 && key <= 126)
		m->matrix[key < 125 ? X : Y][S] += m->matrix[S][S]
						* (key == 124 || key == 125 ? 1 : -1);
	else if (key >= 18 && key <= 29)
		change_color(m, key);
	else if (key == 51)
		init_matrix(m);
	else if (key == 33)
		m->matrix[S][Z] *= 1.05;
	else if (key == 30)
		m->matrix[S][Z] *= 0.95;
	else if (key == 69)
		m->matrix[S][S] *= 1.1;
	else if (key == 78)
		m->matrix[S][S] *= 0.9;
	print(m);
}

void	mouse_press(int button, int x, int y, t_fdf *m)
{
	m->mouse.x = x;
	m->mouse.y = y;
	if (button == 1)
		m->mouse.m1_pressed = 1;
	else if (button == 2)
		m->mouse.m2_pressed = 1;
	else if (button == 3)
		m->mouse.m3_pressed = 1;
	else if (button == 4)
		m->matrix[S][S] *= 0.8;
	else if (button == 5)
		m->matrix[S][S] *= 1.2;
	print(m);
}

void	mouse_release(int button, int x, int y, t_fdf *m)
{
	m->mouse.x = x;
	m->mouse.y = y;
	if (button == 1)
		m->mouse.m1_pressed = 0;
	else if (button == 2)
		m->mouse.m2_pressed = 0;
	else if (button == 3)
		m->mouse.m3_pressed = 0;
}

void	mouse_move(int x, int y, t_fdf *m)
{
	if (m->mouse.m1_pressed == 1)
	{
		rotate(m, -2, m->mouse.x - x);
		rotate(m, -3, y - m->mouse.y);
	}
	else if (m->mouse.m2_pressed == 1)
	{
		rotate(m, -1, (m->mouse.x - x) / (y < m->height / 2 ? 2 : -2));
		rotate(m, -1, (m->mouse.y - y) / (x < m->width / 2 ? -2 : 2));
	}
	else if (m->mouse.m3_pressed == 1)
	{
		m->matrix[X][S] += x - m->mouse.x;
		m->matrix[Y][S] += y - m->mouse.y;
	}
	else
		return ;
	m->mouse.x = x;
	m->mouse.y = y;
	print(m);
}
