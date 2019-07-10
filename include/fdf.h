/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:52 by smorty            #+#    #+#             */
/*   Updated: 2019/07/10 22:48:14 by smorty           ###   ########.fr       */
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

#define FDF_WIDTH 1920
#define FDF_HEIGHT 1200

#define TOP_CLR 0x8b0000
#define GRND_CLR 0x228b22
#define BTM_CLR 0x483d8b

#define RED_CH(color) ((color >> 16) & 0xFF)
#define GREEN_CH(color) ((color >> 8) & 0xFF)
#define BLUE_CH(color) (color & 0xFF)
#define MIN(a, b) (a < b ? a : b)

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
	int				m2_pressed;
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
	t_mouse			mouse;
	t_image			image;
	int				width;
	int				height;
	int				def_scale;
	int				scale;
	int				projection;
}				t_fdf;

t_dots			*read_map(int fd, int *scale);
int				get_color(int color0, int color1, int n, int len);
void			print(t_fdf *m);
void			rotate_x(t_dots *coord, double angle, int projection);
void			rotate_y(t_dots *coord, double angle, int projection);
void			rotate_z(t_dots *coord, double angle, int projection);
void			shift(t_dots *coord, int key);
void			key_press(int keycode, t_fdf *m);
void			key_release(int keycode, t_fdf *m);
void			mouse_press(int button, int x, int y, t_fdf *m);
void			mouse_move(int x, int y, t_fdf *m);
void			mouse_release(int button, int x, int y, t_fdf *m);
int				parallel(t_dots *coord);
int				isometry(t_dots *coord);
void			mirror(t_dots *coord);

#endif