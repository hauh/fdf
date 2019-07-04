/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:18 by smorty            #+#    #+#             */
/*   Updated: 2019/07/04 23:20:44 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_mlx *m, double angle)
{
	t_dots	*tmp;
	double	y;
	double	z;

	tmp = m->coord;
	while (tmp)
	{
		y = tmp->y;
		z = tmp->z;
		tmp->y = y * cos(angle) + z * sin(angle);
		tmp->z = -y * sin(angle) + z * cos(angle);
		tmp = tmp->right;
	}
}

void	rotate_y(t_mlx *m, double angle)
{
	t_dots	*tmp;
	double	x;
	double	z;

	tmp = m->coord;
	while (tmp)
	{
		x = tmp->x;
		z = tmp->z;
		tmp->x = x * cos(angle) + z * sin(angle);
		tmp->z = -x * sin(angle) + z * cos(angle);
		tmp = tmp->right;
	}
}

void	rotate_z(t_mlx *m, double angle)
{
	t_dots	*tmp;
	double	x;
	double	y;

	tmp = m->coord;
	while (tmp)
	{
		x = tmp->x;
		y = tmp->y;
		tmp->x = x * cos(angle) - y * sin(angle);
		tmp->y = x * sin(angle) + y * cos(angle);
		tmp = tmp->right;
	}
}

void	shift(t_dots *coord, int key)
{
	double	shift;

	shift = (key == 124 || key == 125 ? 1 : -1);
	if (key == 123 || key == 124)
		while (coord)
		{
			coord->x += shift;
			coord = coord->right;
		}
	else
		while (coord)
		{
			coord->y += shift;
			coord = coord->right;
		}
}

void	draw_vertical(t_mlx *m, int x, int y0, int y1)
{
	int dir;

	dir = y1 > y0 ? 1 : -1;
	while (y0 != y1)
	{
		mlx_pixel_put(m->mlx_p, m->win_p, x, y0, 185155200);
		y0 += dir;
	}
}

void	draw_line(t_mlx *m, int x0, int x1, int y0, int y1)
{
	int delta_x;
    int delta_y;
    int error;
    int delta_err;
    int y;
	int x;
    int dir_y;

	delta_x = abs(x1 - x0);
	delta_y = abs(y1 - y0);
	error = 0;
	delta_err = delta_y;
	y = y0;
	x = x0;
	dir_y = y1 - y0;
	if (dir_y > 0)
		dir_y = 1;
	if (dir_y < 0)
		dir_y = -1;
	while (x <= x1)
	{
		mlx_pixel_put(m->mlx_p, m->win_p, x, y, 185155200);
		error += delta_err;
		if (error * 2 >= delta_x)
		{
			y += dir_y;
			error -= delta_x;
		}
		++x;
	}
}

void	print(t_mlx *m)
{
	t_dots		*tmp;
	t_dots		*tmp2;
	int			x;
	int			y;
	int			x0;
	int			y0;

	mlx_clear_window(m->mlx_p, m->win_p);
	tmp = m->coord;
	x = 0;
	y = 0;
	while (tmp)
	{
		x0 = (int)round(tmp->x * m->scale) + m->width / 2;
		y0 = (int)round(tmp->y * m->scale) + m->height / 2;
		tmp = tmp->right;
		if (tmp && tmp->y0 == tmp->left->y0)
		{
			x = (int)round(tmp->x * m->scale) + m->width / 2;
			y = (int)round(tmp->y * m->scale) + m->height / 2;
			draw_line(m, x0, x, y0, y);
			tmp2 = tmp->right;
			while (tmp2 && tmp2->x0 != tmp->x0)
				tmp2 = tmp2->right;
			if (tmp2 && tmp2->left)
			{
				x = (int)round(tmp2->left->x * m->scale) + m->width / 2;
				y = (int)round(tmp2->left->y * m->scale) + m->height / 2;
				x0 == x ? draw_vertical(m, x, y0, y) : draw_line(m, x0, x, y0, y);
			}
		}
		mlx_pixel_put(m->mlx_p, m->win_p, x0, y0, 185255100);
	}
}

void	restore(t_dots *coord)
{
	while (coord)
	{
		coord->x = (double)coord->x0;
		coord->y = (double)coord->y0;
		coord->z = (double)coord->z0;
		coord = coord->right;
	}
}

int	key_press(int key, t_mlx *m)
{

	if (key == 53)
		exit(1);
	else if (key == 1 || key == 13)
		rotate_x(m, (M_PI_4 / 8) * (key == 1 ? 1 : -1));
	else if (key == 12 || key == 14)
		rotate_y(m, (M_PI_4 / 8) * (key - 13));
	else if (key == 0 || key == 2)
		rotate_z(m, (M_PI_4 / 8) * (key - 1));
	else if (key >= 123 && key <= 126)
		shift(m->coord, key);
	else if (key == 51)
		restore(m->coord);
	else if (key == 69)
		++m->scale;
	else if (key == 78 && m->scale)
		--m->scale;
	print(m);
	return (0);
}

void		basis_vector(t_mlx *m)
{
	m->vector[X][X] = 1;
	m->vector[X][Y] = 0;
	m->vector[X][Z] = 0;
	m->vector[Y][X] = 0;
	m->vector[Y][Y] = 1;
	m->vector[Y][Z] = 0;
	m->vector[Z][X] = 0;
	m->vector[Z][Y] = 0;
	m->vector[Z][Z] = 1;
}

int			main(int argc, char **argv)
{
	int		fd;
	t_mlx	*m;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	m = (t_mlx *)malloc(sizeof(t_mlx));
	m->coord = read_map(fd);
	basis_vector(m);
	m->scale = 20;
	m->width = 1000;
	m->height = 1000;
	m->mlx_p = mlx_init();
	m->win_p = mlx_new_window(m->mlx_p, m->width, m->height, "smorty");
	mlx_string_put(m->mlx_p, m->win_p, 900, 10, 185255100, "smorty");
	print(m);
	mlx_hook(m->win_p, 2, 0, key_press, m);
	mlx_loop(m->mlx_p);
	return (0);
} 