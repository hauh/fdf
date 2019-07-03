/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:44:52 by smorty            #+#    #+#             */
/*   Updated: 2019/07/03 22:55:09 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <math.h>
#include "get_next_line.h"

typedef struct	s_dots
{
	double				x;
	double				y;
	double				z;
	struct s_dots	*left;
	struct s_dots	*right;
}				t_dots;

typedef struct	s_mlx
{
	void			*mlx_p;
	void			*win_p;
	t_dots			*coord;
	int				width;
	int				height;
	int				depth;
}				t_mlx;

t_dots			*read_map(int fd);

#endif