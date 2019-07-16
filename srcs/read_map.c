/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:40:45 by smorty            #+#    #+#             */
/*   Updated: 2019/07/16 21:20:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_dots	*new_element(t_dots *list, int x, int y, int z)
{
	t_dots *new;

	if (!(new = (t_dots *)malloc(sizeof(t_dots))))
		exit(-1);
	new->x0 = x;
	new->y0 = y;
	new->z0 = z;
	new->right = NULL;
	new->left = list;
	if (new->left)
		new->left->right = new;
	return (new);
}

static void		centering(t_dots *coord, int x_shift, int y_shift)
{
	while (coord)
	{
		coord->x0 -= x_shift;
		coord->y0 -= y_shift;
		coord = coord->right;
	}
}

static void		down_linking(t_dots *coord)
{
	t_dots	*tmp;

	while (coord)
	{
		tmp = coord->right;
		while (tmp && tmp->x0 != coord->x0)
			tmp = tmp->right;
		coord->down = tmp;
		coord = coord->right;
	}
}

static t_dots	*get_coords(int fd, int *x, int *y)
{
	t_dots	*coord;
	char	**split;
	char	*line;
	int		i;

	coord = NULL;
	while ((i = get_next_line(fd, &line)))
	{
		if (i < 0 || !(split = ft_strsplit((const char *)line, ' ')))
			exit(-1);
		*x = 0;
		while (*split)
			coord = new_element(coord, (*x)++, *y, ft_atoi(*split++));
		i = *x;
		while (i--)
			free(*--split);
		++(*y);
		free(split);
		free(line);
	}
	if (coord)
		while (coord->left)
			coord = coord->left;
	return (coord);
}

t_dots			*read_map(int fd, double *scale)
{
	t_dots	*coord;
	int		fig_width;
	int		fig_height;

	fig_width = 0;
	fig_height = 0;
	if ((coord = get_coords(fd, &fig_width, &fig_height)))
	{
		centering(coord, fig_width / 2, fig_height / 2);
		down_linking(coord);
		*scale = MAX(FDF_HEIGHT / fig_height, FDF_WIDTH / fig_width) / 2.3;
	}
	return (coord);
}
