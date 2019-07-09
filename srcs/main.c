/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:18 by smorty            #+#    #+#             */
/*   Updated: 2019/07/09 21:29:28 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
int		max_z(t_dots *coord)
{
	int z;

	z = coord->z0;
	while (coord)
	{
		if (coord->z0 > z)
			z = coord->z0;
		coord = coord->right;
	}
	return (z);
}*/

int			main(int argc, char **argv)
{
	int		fd;
	t_fdf	*m;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	m = (t_fdf *)malloc(sizeof(t_fdf));
	m->coord = read_map(fd);
	m->scale = 5;
	m->width = 1920;
	m->height = 1200;
	m->mouse.m1_pressed = 0;
	m->mouse.x = 0;
	m->mouse.y = 0;
	m->mlx_p = mlx_init();
	m->win_p = mlx_new_window(m->mlx_p, m->width, m->height, "smorty");
	mlx_string_put(m->mlx_p, m->win_p, 900, 10, 185255100, "smorty");
	m->image.img_p = mlx_new_image(m->mlx_p, m->width, m->height);
	m->image.map = mlx_get_data_addr(m->image.img_p, &m->image.bpp, &m->image.size_line, &m->image.endian);
	print(m);
	mlx_hook(m->win_p, 2, 0, (int (*)())key_press, m);
	mlx_hook(m->win_p, 4, 0, (int (*)())mouse_press, m);
	mlx_hook(m->win_p, 6, 0, (int (*)())mouse_move, m);
	mlx_hook(m->win_p, 5, 0, (int (*)())mouse_release, m);
	mlx_loop(m->mlx_p);
	return (0);
} 