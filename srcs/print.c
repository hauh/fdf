/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:41:21 by smorty            #+#    #+#             */
/*   Updated: 2019/07/16 22:47:13 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_matrix(t_dots *coord, double matrix[4][4])
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

static void	print_controls(t_fdf *m)
{
	int x;

	x = 0;
	mlx_string_put(m->mlx_p, m->win_p, 10, x, 0xffffff, "Controls:");
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
	mlx_string_put(m->mlx_p, m->win_p, 10, x += 18, 0xffffff, "Exit: esc");
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
