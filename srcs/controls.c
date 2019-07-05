/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:35:28 by smorty            #+#    #+#             */
/*   Updated: 2019/07/05 22:59:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_press(int key, t_mlx *m)
{
	if (key == 53)
		exit(0);
	else if (key == 34)
		isometry(m->coord);
//	else if (key == 46)
//		mirror(m->coord);
	else if (key == 1 || key == 13)
		rotate_x(m->coord, (M_PI_4 / 8) * (key == 1 ? 1 : -1));
	else if (key == 12 || key == 14)
		rotate_y(m->coord, (M_PI_4 / 8) * (key - 13));
	else if (key == 0 || key == 2)
		rotate_z(m->coord, (M_PI_4 / 8) * (key - 1));
	else if (key >= 123 && key <= 126)
		shift(m->coord, key);
	else if (key == 51)
		restore(m->coord);
	else if (key == 69)
		++m->scale;
	else if (key == 78 && m->scale)
		--m->scale;
	print(m);
}

/*void	key_release(int key, t_mlx *m)
{

}*/

void	mouse_press(int button, int x, int y, t_mlx *m)
{
	m->mouse.x = x;
	m->mouse.y = y;
	if (button == 1)
		m->mouse.m1_pressed = 1;
}

void	mouse_release(int button, int x, int y, t_mlx *m)
{
	m->mouse.x = x;
	m->mouse.y = y;
	if (button == 1)
		m->mouse.m1_pressed = 0;
}

void	mouse_move(int x, int y, t_mlx *m)
{
	if (m->mouse.m1_pressed == 1)
	{
		rotate_y(m->coord, (M_PI_4 / 64) * (x - m->mouse.x));
		rotate_x(m->coord, (M_PI_4 / 64) * (y - m->mouse.y));
		m->mouse.x = x;
		m->mouse.y = y;
		print(m);
	}
}
