/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:35:28 by smorty            #+#    #+#             */
/*   Updated: 2019/07/11 23:08:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_press(int key, t_fdf *m)
{
	if (key == 53)
		exit(0);
	else if (key == 34)
		isometry(m->coord);
	else if (key == 48)
		m->tab_pressed = ~m->tab_pressed;
//	else if (key == 46)
//		mirror(m->coord);
	else if (key == 1 || key == 13)
		m->angle[X] += (M_PI_4 / 8) * (key == 13 ? 1 : -1);
	else if (key == 12 || key == 14)
		m->angle[Y] += (M_PI_4 / 8) * (key - 13);
	else if (key == 0 || key == 2)
		m->angle[Z] += (M_PI_4 / 8) * (key - 1);
	else if (key >= 123 && key <= 126)
		m->shift[key < 125 ? X : Y] += (key == 124 || key == 125 ?
										m->scale : -m->scale);
	else if (key >= 18 && key <= 29)
		change_color(m, key);
	else if (key == 51)
		init_matrix(m);
	else if (key == 69)
		++m->scale;
	else if (key == 78 && m->scale > 0)
		--m->scale;
	print(m);
}

/*void	key_release(int key, t_fdf *m)
{

}*/

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
	else if (button == 5)
		m->scale += 2;
	else if (button == 4)
		if ((m->scale -= 2) < 0)
			m->scale = 0;
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

void	mouse_shift(double x, double y, int scale, t_dots *coord)
{
	x /= scale;
	y /= scale;
	while (coord)
	{
		coord->x += x;
		coord->y += y;
		coord = coord->right;
	}
}

void	mouse_move(int x, int y, t_fdf *m)
{
	if (m->mouse.m1_pressed == 1)
	{
		m->angle[X] += (M_PI_4 / 64) * (m->mouse.y - y);
		m->angle[Y] += (M_PI_4 / 64) * (x - m->mouse.x);
	}
	else if (m->mouse.m2_pressed == 1)
	{
		if (y < m->height / 2)
			m->angle[Z] += (M_PI_4 / 64) * (x - m->mouse.x) / 2;
		else
			m->angle[Z] += (M_PI_4 / 64) * (m->mouse.x - x) / 2;
		if (x < m->width / 2)
			m->angle[Z] += (M_PI_4 / 64) * (m->mouse.y - y) / 2;
		else
			m->angle[Z] += (M_PI_4 / 64) * (y - m->mouse.y) / 2;
	}
	else if (m->mouse.m3_pressed == 1)
	{
		m->shift[X] += x - m->mouse.x;
		m->shift[Y] += y - m->mouse.y;
	}
	else
		return ;
	m->mouse.x = x;
	m->mouse.y = y;
	print(m);
}
