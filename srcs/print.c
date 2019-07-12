/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:41:21 by smorty            #+#    #+#             */
/*   Updated: 2019/07/12 20:06:15 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		add_pixel(t_fdf *m, int x, int y, int color)
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

static void		draw_line(t_fdf *m, t_dots *coord0, t_dots *coord1, int x0, int x1, int y0, int y1)
{
	int delta[2];
	int sign[2];
	int error[2];
	int len;
	int n;
	int color;

	delta[X] = abs(x1 - x0);
	delta[Y] = abs(y1 - y0);
	sign[X] = x0 < x1 ? 1 : -1;
	sign[Y] = y0 < y1 ? 1 : -1;
	error[0] = delta[X] - delta[Y];
	len = (int)round(sqrt(delta[X] * delta[X] + delta[Y] * delta[Y]));
	n = 0;
	while (x0 != x1 || y0 != y1)
	{
		color = m->colored ? 0xffffff : get_color(coord0->color, coord1->color, n++, len);
		add_pixel(m, x0, y0, color);
		error[1] = error[0] * 2;
		if (error[1] > -delta[Y]) 
		{
			error[0] -= delta[Y];
			x0 += sign[X];
		}
		if (error[1] < delta[X]) 
		{
			error[0] += delta[X];
			y0 += sign[Y];
		}
	}
	add_pixel(m, x1, y1, coord1->color);
}

static void	connect_dots(t_fdf *m, t_dots *coord)
{
	int			x;
	int			y;
	int			x0;
	int			y0;

	x = 0;
	y = 0;
	while (coord)
	{
		if (!coord->left || coord->left->y0 != coord->y0)
		{
			x0 = (int)round(coord->x);// * m->scale + m->width / 2);
			y0 = (int)round(coord->y);// * m->scale + m->height / 2);
		}
		if (coord->down)
		{
			x = (int)round(coord->down->x);// * m->scale + m->width / 2);
			y = (int)round(coord->down->y);// * m->scale + m->height / 2);
			if ((x0 < m->width || x < m->width) && (y0 < m->height || y < m->height))
				draw_line(m, coord, coord->down, x0, x, y0, y);
		}
		if (coord->right && coord->y0 == coord->right->y0)
		{
			x = (int)round(coord->right->x);// * m->scale + m->width / 2);
			y = (int)round(coord->right->y);// * m->scale + m->height / 2);
			if ((x0 < m->width || x < m->width) && (y0 < m->height || y < m->height))
				draw_line(m, coord, coord->right, x0, x, y0, y);
		}
		coord = coord->right;
		x0 = x;
		y0 = y;
	}
}

static void	print_controls(t_fdf *m)
{
	int x;

	x = 0;
	mlx_string_put(m->mlx_p, m->win_p, 10, x, 0xffffff,
		"Controls:");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Move image: arrows, MMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Zoom: +, -, scroll");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"X-rotation: W, S, RMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Y-rotation: Q, E, LMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Z-rotation: A, D, LMB");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Change colors: 1 - 9");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Toggle coloring: 0");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
		"Default position & colors: backspace");
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 17, 0xffffff,
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


