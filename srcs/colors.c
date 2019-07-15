/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 21:50:16 by smorty            #+#    #+#             */
/*   Updated: 2019/07/15 20:53:13 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_color(int color0, int color1, int n, int len)
{
	int red;
	int green;
	int blue;

	red = (RED_CH(color1) - RED_CH(color0)) * n / len + RED_CH(color0);
	green = (GREEN_CH(color1) - GREEN_CH(color0)) * n / len + GREEN_CH(color0);
	blue = (BLUE_CH(color1) - BLUE_CH(color0)) * n / len + BLUE_CH(color0);
	return ((red << 16) | (green << 8) | blue);
}

void	coloring(t_dots *coord, int color0, int color1)
{
	int		max_z;
	int		min_z;
	t_dots	*head;

	max_z = 0;
	min_z = 0;
	head = coord;
	while (coord)
	{
		if (coord->z0 > max_z)
			max_z = coord->z0;
		if (coord->z0 < min_z)
			min_z = coord->z0;
		coord = coord->right;
	}
	min_z = ~min_z + 1;
	max_z += min_z + 1;
	while (head)
	{
		head->color = get_color(color0, color1, head->z0 + min_z, max_z);
		head = head->right;
	}
}

void	change_color(t_fdf *m, int key)
{
	if (key == 18)
		coloring(m->coord, CLR_10, CLR_11);
	else if (key == 19)
		coloring(m->coord, CLR_20, CLR_21);
	else if (key == 20)
		coloring(m->coord, CLR_30, CLR_31);
	else if (key == 21)
		coloring(m->coord, CLR_40, CLR_41);
	else if (key == 22)
		coloring(m->coord, CLR_50, CLR_51);
	else if (key == 23)
		coloring(m->coord, CLR_60, CLR_61);
	else if (key == 25)
		coloring(m->coord, CLR_70, CLR_71);
	else if (key == 26)
		coloring(m->coord, CLR_80, CLR_81);
	else if (key == 28)
		coloring(m->coord, CLR_90, CLR_91);
	else if (key == 29)
		coloring(m->coord, ((RED_CH(rand()) << 16) | (GREEN_CH(rand()) << 8)
							| (BLUE_CH(rand()))), ((RED_CH(rand()) << 16)
							| (GREEN_CH(rand()) << 8 | BLUE_CH(rand()))));
	else if (key == 27)
		m->colored = ~m->colored;
}
