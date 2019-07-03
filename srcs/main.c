/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:18 by smorty            #+#    #+#             */
/*   Updated: 2019/07/03 23:29:42 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>
void	rotate(t_dots *coord, double angle)
{
	double rx;
	double ry;

	while (coord)
	{
		rx = coord->x;
		ry = coord->y;
		coord->x = rx * cos(angle) - ry * sin(angle);
		coord->y = rx * sin(angle) + ry * cos(angle);
		coord = coord->right;
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

void	print(t_mlx *m)
{
	t_dots		*tmp;
	int			x;
	int			y;

	mlx_clear_window(m->mlx_p, m->win_p);
	tmp = m->coord;
	while (tmp)
	{
		x = tmp->x * 20 + 400;
		y = tmp->y * 20 + 400;
			mlx_pixel_put(m->mlx_p, m->win_p, x, y, 185255100);
		tmp = tmp->right;
	}
}

int	key_press(int key, t_mlx *m)
{

	if (key == 53)
		exit(1);
	else if (key == 30)
	{
		rotate(m->coord, M_PI_4 / 2);
		print(m);
	}
	else if (key >= 123 && key <= 126)
	{
		shift(m->coord, key);
		print(m);
	}
	return (0);
}


#include <stdio.h>
int			main(int argc, char **argv)
{
	int		fd;
	t_mlx	*m;
	t_dots	*tmp;
	int		i;
	int x;
	int y;
//	void	*image;

	if (argc != 2 || (fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	m = (t_mlx *)malloc(sizeof(t_mlx));
	m->coord = read_map(fd);
	m->mlx_p = mlx_init();
	m->win_p = mlx_new_window(m->mlx_p, 1000, 1000, "smorty");
//	image = mlx_new_image(mlx_ptr, 100, 100);
//	mlx_put_image_to_window(mlx_ptr, window, image, 200, 200);
	mlx_string_put(m->mlx_p, m->win_p, 900, 10, 185255100, "smorty");
	tmp = m->coord;
	while (tmp)
	{
		i = 0;
		x = tmp->x * 20 + 400;
		y = tmp->y * 20 + 400;
		mlx_pixel_put(m->mlx_p, m->win_p, x, y, 185255100);
		// if (m->coord->left && m->coord->left->y == m->coord->y)
		// {
		// 	i = 0;
		// 	while (i++ < 20)
		// 		mlx_pixel_put(m->mlx_p, m->win_p, (m->coord->x + 1) * 20 - i, (m->coord->y + 1) * 20, 185255100);
		// }
		// if (m->coord->y != 10)
		// {
		// 	i = 0;
		// 	while (i++ < 20)
		// 		mlx_pixel_put(m->mlx_p, m->win_p, (m->coord->x + 1) * 20, (m->coord->y + 1) * 20 + i, 185255100);
		// }
		tmp = tmp->right;
	}
	mlx_hook(m->win_p, 2, 0, key_press, m);
	mlx_loop(m->mlx_p);
	return (0);
} 