/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:41:21 by smorty            #+#    #+#             */
/*   Updated: 2019/07/15 23:42:40 by smorty           ###   ########.fr       */
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

static void	draw_line(t_fdf *m, t_dots *coord0, t_dots *coord1, int dots[4])
{
	int delta[2];
	int sign[2];
	int error[2];
	int len;
	int n;

	delta[X] = abs(dots[X + 2] - dots[X]);
	delta[Y] = abs(dots[Y + 2] - dots[Y]);
	sign[X] = dots[X] < dots[X + 2] ? 1 : -1;
	sign[Y] = dots[Y] < dots[Y + 2] ? 1 : -1;
	error[0] = delta[X] - delta[Y];
	len = (int)round(sqrt(delta[X] * delta[X] + delta[Y] * delta[Y]));
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

static void	connect_dots(t_fdf *m, t_dots *coord)
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

static void	print_controls(t_fdf *m)
{
	int x;

	x = 0;
	mlx_string_put(m->mlx_p, m->win_p, 10, x, 0xffffff, "Controls:");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff, "Isometry: I");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Move image: arrows, MMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Zoom: Num+, Num-, scroll");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"X-rotation: W, S, RMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Y-rotation: Q, E, LMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Z-rotation: A, D, LMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Scale height: [, ]");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Change colors: 1 - 9, 0 - random");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Toggle coloring: -");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Default position & colors: backspace");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff,
		"Hide controls: tab");
}

void		print(t_fdf *m)
{
	apply_matrix(m->coord, m->matrix);
	mlx_clear_window(m->mlx_p, m->win_p);
	ft_bzero(m->image.map, m->width * m->height * 4);
	connect_dots(m, m->coord);
	mlx_put_image_to_window(m->mlx_p, m->win_p, m->image.img_p, 0, 0);
	if (!m->tab_pressed)
		print_controls(m);
}
