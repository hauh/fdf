/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:41:21 by smorty            #+#    #+#             */
/*   Updated: 2019/07/11 00:14:31 by smorty           ###   ########.fr       */
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

int				get_color(int color0, int color1, int n, int len)
{
	int red;
	int green;
	int blue;

	red = (RED_CH(color1) - RED_CH(color0)) * n / len + RED_CH(color0);
	green = (GREEN_CH(color1) - GREEN_CH(color0)) * n / len + GREEN_CH(color0);
	blue = (BLUE_CH(color1) - BLUE_CH(color0)) * n / len + BLUE_CH(color0);
	return ((red << 16) | (green << 8) | blue);
}

static void		draw_line(t_fdf *m, t_dots *coord0, t_dots *coord1, int x0, int x1, int y0, int y1)
{
	int deltaX = abs(x1 - x0);
	int deltaY = abs(y1 - y0);
	int signX = x0 < x1 ? 1 : -1;
	int signY = y0 < y1 ? 1 : -1;
	int error = deltaX - deltaY;
	int len;
	int n = 0;
	int color;

	len = (int)round(sqrt(deltaX * deltaX + deltaY * deltaY));
	while (x0 != x1 || y0 != y1)
	{
		color = get_color(coord0->color, coord1->color, n++, len);
		add_pixel(m, x0, y0, color);
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
			x0 = (int)round(coord->x * m->scale) + m->width / 2;
			y0 = (int)round(coord->y * m->scale) + m->height / 2;
		}
		if (coord->down)
		{
			x = (int)round(coord->down->x * m->scale) + m->width / 2;
			y = (int)round(coord->down->y * m->scale) + m->height / 2;
			if ((x0 < m->width || x < m->width) && (y0 < m->height || y < m->height))
				draw_line(m, coord, coord->down, x0, x, y0, y);
		}
		if (coord->right && coord->y0 == coord->right->y0)
		{
			x = (int)round(coord->right->x * m->scale) + m->width / 2;
			y = (int)round(coord->right->y * m->scale) + m->height / 2;
			if ((x0 < m->width || x < m->width) && (y0 < m->height || y < m->height))
				draw_line(m, coord, coord->right, x0, x, y0, y);
		}
		coord = coord->right;
		x0 = x;
		y0 = y;
	}
}

void		print(t_fdf *m)
{
	mlx_clear_window(m->mlx_p, m->win_p);
	ft_bzero(m->image.map, m->width * m->height * 4);
	connect_dots(m, m->coord);
	mlx_put_image_to_window(m->mlx_p, m->win_p, m->image.img_p, 0, 0);
}
