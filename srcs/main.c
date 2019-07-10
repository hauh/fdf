/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:18 by smorty            #+#    #+#             */
/*   Updated: 2019/07/10 22:48:40 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		cleanup(t_fdf *m)
{
	while (m->coord->right)
		free(m->coord->right);
	free(m->coord);
	free(m->image.img_p);
	free(m->image.map);
	free(m->mlx_p);
	free(m->win_p);
	free(m);
}

static t_fdf	*initialization(int fd)
{
	t_fdf *m;

	if (!(m = (t_fdf *)malloc(sizeof(t_fdf))))
		exit(-1);
	m->width = FDF_WIDTH;
	m->height = FDF_HEIGHT;
	m->coord = read_map(fd, &m->def_scale);
	m->scale = m->def_scale;
	m->projection = 1;
	m->mouse.m1_pressed = 0;
	m->mouse.m2_pressed = 0;
	m->mouse.x = 0;
	m->mouse.y = 0;
	m->mlx_p = mlx_init();
	m->win_p = mlx_new_window(m->mlx_p, m->width, m->height, "smorty's FdF");
	m->image.img_p = mlx_new_image(m->mlx_p, m->width, m->height);
	m->image.map = mlx_get_data_addr(m->image.img_p, &m->image.bpp,
									&m->image.size_line, &m->image.endian);
	return (m);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_fdf	*m;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	m = initialization(fd);
	print(m);
	mlx_hook(m->win_p, 2, 0, (int (*)())key_press, m);
	mlx_hook(m->win_p, 4, 0, (int (*)())mouse_press, m);
	mlx_hook(m->win_p, 6, 0, (int (*)())mouse_move, m);
	mlx_hook(m->win_p, 5, 0, (int (*)())mouse_release, m);
	mlx_loop(m->mlx_p);
	cleanup(m);
	return (0);
} 