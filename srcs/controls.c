/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:35:28 by smorty            #+#    #+#             */
/*   Updated: 2019/07/10 23:41:39 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_press(int key, t_fdf *m)
{
	if (key == 53)
		exit(0);
	else if (key == 34)
	{
		m->projection = isometry(m->coord);
		m->scale = m->def_scale / 3;
	}
//	else if (key == 46)
//		mirror(m->coord);
	else if (key == 1 || key == 13)
		rotate_x(m->coord, (M_PI_4 / 8) * (key == 1 ? 1 : -1), m->projection);
	else if (key == 12 || key == 14)
		rotate_y(m->coord, (M_PI_4 / 8) * (key - 13), m->projection);
	else if (key == 0 || key == 2)
		rotate_z(m->coord, (M_PI_4 / 8) * (key - 1), m->projection);
	else if (key >= 123 && key <= 126)
		shift(m->coord, key);
	else if (key == 51)
	{
		m->projection = parallel(m->coord);
		m->scale = m->def_scale;
	}
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
		rotate_y(m->coord, (M_PI_4 / 64) * (x - m->mouse.x), m->projection);
		rotate_x(m->coord, (M_PI_4 / 64) * (y - m->mouse.y), m->projection);
		m->mouse.x = x;
		m->mouse.y = y;
		print(m);
	}
	else if (m->mouse.m2_pressed == 1)
	{
		mouse_shift(x - m->mouse.x, y - m->mouse.y, m->scale, m->coord);
		m->mouse.x = x;
		m->mouse.y = y;
		print(m);
	}
}
