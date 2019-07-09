/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:52 by smorty            #+#    #+#             */
/*   Updated: 2019/07/09 21:30:54 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <math.h>
#include "get_next_line.h"
#include <stdio.h> //remove

# define X 0
# define Y 1
# define Z 2

#define RED_CH(color) ((color >> 16) & 0xFF)
#define GREEN_CH(color) ((color >> 8) & 0xFF)
#define BLUE_CH(color) (color & 0xFF)

#define TOP_COLOR 0x8b0000
#define GROUND_COLOR 0xee9a00
#define BOTTOM_COLOR 0x8a2be2

typedef struct	s_dots
{
	double			x;
	double			y;
	double			z;
	int				x0;
	int				y0;
	int				z0;
	int				color;
	struct s_dots	*down;
	struct s_dots	*left;
	struct s_dots	*right;
}				t_dots;

typedef struct	s_mouse
{
	int				x;
	int				y;
	int				m1_pressed;
}				t_mouse;

typedef struct	s_image
{
	void			*img_p;
	char			*map;
	int				bpp;
	int				size_line;
	int				endian;
}				t_image;

typedef struct	s_fdf
{
	void			*mlx_p;
	void			*win_p;
	t_dots			*coord;
	t_image			image;
	t_mouse			mouse;
	int				scale;
	int				width;
	int				height;
}				t_fdf;

t_dots			*read_map(int fd);
int				get_color(int color0, int color1, int n, int len);
void			print(t_fdf *m);
void			rotate_x(t_dots *coord, double angle);
void			rotate_y(t_dots *coord, double angle);
void			rotate_z(t_dots *coord, double angle);
void			shift(t_dots *coord, int key);
void			restore(t_dots *coord);
void			key_press(int keycode, t_fdf *m);
void			key_release(int keycode, t_fdf *m);
void			mouse_press(int button, int x, int y, t_fdf *m);
void			mouse_move(int x, int y, t_fdf *m);
void			mouse_release(int button, int x, int y, t_fdf *m);
void			isometry(t_dots *coord);
void			mirror(t_dots *coord);

#endif