/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:52 by smorty            #+#    #+#             */
/*   Updated: 2019/07/12 23:27:57 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <math.h>
#include "get_next_line.h"
#include <stdio.h> //remove
#include <time.h>

# define X 0
# define Y 1
# define Z 2
# define S 3

#define FDF_WIDTH 1920
#define FDF_HEIGHT 1200

#define CLR_00 0x228B22
#define CLR_01 0x8B0000
#define CLR_10 0x314fe0
#define CLR_11 0x9a017b
#define CLR_20 0x25f871
#define CLR_21 0xff124a
#define CLR_30 0x48748d
#define CLR_31 0xfac370
#define CLR_40 0xdff94d
#define CLR_41 0xe35406
#define CLR_50 0xf53a11
#define CLR_51 0xedd0c5
#define CLR_60 0x962459
#define CLR_61 0x2beaf3
#define CLR_70 0x07e8f8
#define CLR_71 0x37021b
#define CLR_80 0xb2e1c7
#define CLR_81 0x4b197a
#define CLR_90 0x388988
#define CLR_91 0xd89201

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
	int				m3_pressed;
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
	double			matrix[4][4];
	double			angle[3];
	int				width;
	int				height;
	int				colored;
	int 			tab_pressed;
}				t_fdf;

t_dots			*read_map(int fd, double *scale);
void			coloring(t_dots *coord, int color0, int color1);
int				get_color(int color0, int color1, int n, int len);
void			print(t_fdf *m);
void			change_color(t_fdf *m, int key);
void			shift(t_dots *coord, int key);
void			key_press(int keycode, t_fdf *m);
void			key_release(int keycode, t_fdf *m);
void			mouse_press(int button, int x, int y, t_fdf *m);
void			mouse_move(int x, int y, t_fdf *m);
void			mouse_release(int button, int x, int y, t_fdf *m);
int				parallel(t_dots *coord);
int				isometry(t_dots *coord);
void			mirror(t_dots *coord);
void			init_matrix(t_fdf *m);
void			rotate(t_fdf *m, int key, int distance);
void			apply_matrix(t_dots *coord, double matrix[4][4]);

#endif