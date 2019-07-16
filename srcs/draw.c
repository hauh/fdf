/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:17:30 by smorty            #+#    #+#             */
/*   Updated: 2019/07/16 21:51:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_pixel(t_fdf *m, int x, int y, int color)
{
	int pixel;

	if (x > 0 && x < m->width && y > 0 && y < m->height)
	{
		pixel = (x * m->image.bpp / 8) + (y * m->image.size_line);
		m->image.map[pixel] = color;
		m->image.map[++pixel] = color >> 8;
		m->image.map[++pixel] = color >> 16;
		m->image.map[++pixel] = 0;
	}
}

static int	line_params(int delta[2], int sign[2], int error[2], int dots[4])
{
	int len;

	delta[X] = abs(dots[X + 2] - dots[X]);
	delta[Y] = abs(dots[Y + 2] - dots[Y]);
	sign[X] = dots[X] < dots[X + 2] ? 1 : -1;
	sign[Y] = dots[Y] < dots[Y + 2] ? 1 : -1;
	error[0] = delta[X] - delta[Y];
	len = (int)round(sqrt(delta[X] * delta[X] + delta[Y] * delta[Y]));
	return (len);
}

static void	draw_line(t_fdf *m, t_dots *coord0, t_dots *coord1, int dots[4])
{
	int delta[2];
	int sign[2];
	int error[2];
	int len;
	int n;

	len = line_params(delta, sign, error, dots);
	n = 0;
	while (dots[X] != dots[X + 2] || dots[Y] != dots[Y + 2])
	{
		add_pixel(m, dots[X], dots[Y], m->colored ? 0xffffff :
					get_color(coord0->color, coord1->color, n++, len));
		error[1] = error[0] * 2;
		if (error[1] > -delta[Y])
		{
			error[0] -= delta[Y];
			dots[X] += sign[X];
		}
		if (error[1] < delta[X])
		{
			error[0] += delta[X];
			dots[Y] += sign[Y];
		}
	}
	add_pixel(m, dots[X + 2], dots[Y + 2], coord1->color);
}

void		connect_dots(t_fdf *m, t_dots *coord)
{
	int dots[4];

	while (coord)
	{
		if (coord->down)
		{
			dots[X] = (int)round(coord->x);
			dots[Y] = (int)round(coord->y);
			dots[X + 2] = (int)round(coord->down->x);
			dots[Y + 2] = (int)round(coord->down->y);
			draw_line(m, coord, coord->down, dots);
		}
		if (coord->right && coord->y0 == coord->right->y0)
		{
			dots[X] = (int)round(coord->x);
			dots[Y] = (int)round(coord->y);
			dots[X + 2] = (int)round(coord->right->x);
			dots[Y + 2] = (int)round(coord->right->y);
			draw_line(m, coord, coord->right, dots);
		}
		coord = coord->right;
	}
}
