/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:35:28 by smorty            #+#    #+#             */
/*   Updated: 2019/07/16 21:45:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cleanup(t_fdf *m)
{
	while (m->coord->right)
	{
		m->coord = m->coord->right;
		free(m->coord->left);
	}
	free(m->coord);
	free(m->image.img_p);
	free(m->image.map);
	free(m->mlx_p);
	free(m->win_p);
	free(m);
}

void		key_press(int key, t_fdf *m)
{
	if (key == 53)
	{
		cleanup(m);
		exit(0);
	}
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

void		mouse_press(int button, int x, int y, t_fdf *m)
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

void		mouse_release(int button, int x, int y, t_fdf *m)
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

void		mouse_move(int x, int y, t_fdf *m)
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
