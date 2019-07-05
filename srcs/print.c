/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:41:21 by smorty            #+#    #+#             */
/*   Updated: 2019/07/05 21:47:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_mlx *m, int x0, int x1, int y0, int y1)
{
	int deltaX = abs(x1 - x0);
	int deltaY = abs(y1 - y0);
	int signX = x0 < x1 ? 1 : -1;
	int signY = y0 < y1 ? 1 : -1;
	int error = deltaX - deltaY;

	while (x0 != x1 || y0 != y1) 
	{
		mlx_pixel_put(m->mlx_p, m->win_p, x0, y0, 185255100);
		int error2 = error * 2;
		if (error2 > -deltaY) 
		{
			error -= deltaY;
			x0 += signX;
		}
		if (error2 < deltaX) 
		{
			error += deltaX;
			y0 += signY;
		}
	}
	mlx_pixel_put(m->mlx_p, m->win_p, x1, y1, 185255100);
}

void		print(t_mlx *m)
{
	t_dots		*tmp;
	t_dots		*down;
	int			x;
	int			y;
	int			x0;
	int			y0;

	mlx_clear_window(m->mlx_p, m->win_p);
	tmp = m->coord;
	x = 0;
	y = 0;
	while (tmp->right)
	{
		x0 = (int)round(tmp->x * m->scale) + m->width / 2;
		y0 = (int)round(tmp->y * m->scale) + m->height / 2;
		mlx_pixel_put(m->mlx_p, m->win_p, x0, y0, 185255100);
		tmp = tmp->right;
		if (tmp->y0 == tmp->left->y0)
		{
			x = (int)round(tmp->x * m->scale) + m->width / 2;
			y = (int)round(tmp->y * m->scale) + m->height / 2;
			draw_line(m, x0, x, y0, y);
		}
		down = tmp;
		while (down && down->x0 != tmp->left->x0)
			down = down->right;
		if (down)
		{
			x = (int)round(down->x * m->scale) + m->width / 2;
			y = (int)round(down->y * m->scale) + m->height / 2;
			draw_line(m, x0, x, y0, y);
		}
	}
}
