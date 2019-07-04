/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:52 by smorty            #+#    #+#             */
/*   Updated: 2019/07/04 22:25:24 by smorty           ###   ########.fr       */
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

typedef struct	s_dots
{
	double				x;
	double				y;
	double				z;
	int					x0;
	int					y0;
	int					z0;
	struct s_dots	*left;
	struct s_dots	*right;
}				t_dots;

typedef struct	s_mlx
{
	void			*mlx_p;
	void			*win_p;
	t_dots			*coord;
	double			vector[3][3];
	int				scale;
	int				width;
	int				height;
	int				depth;
}				t_mlx;

t_dots			*read_map(int fd);

#endif