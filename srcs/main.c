/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:18 by smorty            #+#    #+#             */
/*   Updated: 2019/07/16 22:32:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			init_matrix(t_fdf *m)
{
	coloring(m->coord, CLR_00, CLR_01);
	m->matrix[X][X] = 1.0;
	m->matrix[X][Y] = 0.0;
	m->matrix[X][Z] = 0.0;
	m->matrix[X][S] = m->width / 2;
	m->matrix[Y][X] = 0.0;
	m->matrix[Y][Y] = 1.0;
	m->matrix[Y][Z] = 0.0;
	m->matrix[Y][S] = m->height / 2;
	m->matrix[Z][X] = 0.0;
	m->matrix[Z][Y] = 0.0;
	m->matrix[Z][Z] = 1.0;
	m->matrix[Z][S] = 0.0;
	m->matrix[S][X] = 1.0;
	m->matrix[S][Y] = 1.0;
	m->matrix[S][Z] = 1.0;
	m->matrix[S][S] = m->def_scale;
	m->angle[X] = -1.0;
	m->angle[Y] = 0.0;
	m->angle[Z] = M_PI_4;
	rotate(m, 0, 0);
}

static t_fdf	*initialization(int fd)
{
	t_fdf *m;

	if (!(m = (t_fdf *)malloc(sizeof(t_fdf))))
		exit(-1);
	m->width = FDF_WIDTH;
	m->height = FDF_HEIGHT;
	m->coord = read_map(fd, &m->def_scale);
	init_matrix(m);
	m->mouse.m1_pressed = 0;
	m->mouse.m2_pressed = 0;
	m->mouse.m3_pressed = 0;
	m->tab_pressed = 0;
	m->colored = 0;
	m->mouse.x = 0;
	m->mouse.y = 0;
	if (!(m->mlx_p = mlx_init()))
		exit(-1);
	m->win_p = mlx_new_window(m->mlx_p, m->width, m->height, "smorty's FdF");
	m->image.img_p = mlx_new_image(m->mlx_p, m->width, m->height);
	if (!(m->win_p && m->image.img_p))
		exit(-1);
	if (!(m->image.map = mlx_get_data_addr(m->image.img_p, &m->image.bpp,
									&m->image.size_line, &m->image.endian)))
		exit(-1);
	return (m);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_fdf	*m;

	if (argc != 2)
		write(1, "usage: fdf map_file\n", 20);
	else if ((fd = open(argv[1], O_RDONLY)) < 0)
		write(1, "file error\n", 11);
	else
	{
		m = initialization(fd);
		close(fd);
		print(m);
		mlx_hook(m->win_p, 2, 0, (int (*)())key_press, m);
		mlx_hook(m->win_p, 4, 0, (int (*)())mouse_press, m);
		mlx_hook(m->win_p, 6, 0, (int (*)())mouse_move, m);
		mlx_hook(m->win_p, 5, 0, (int (*)())mouse_release, m);
		mlx_loop(m->mlx_p);
	}
	return (0);
}
