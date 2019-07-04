/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:40:45 by smorty            #+#    #+#             */
/*   Updated: 2019/07/04 23:22:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_dots	*new_element(t_dots *list, int x, int y, int z)
{
	t_dots *new;

	if (!(new = (t_dots *)malloc(sizeof(t_dots))))
		exit(-1);
	new->x = (double)x;
	new->y = (double)y;
	new->z = (double)z;
	new->x0 = x;
	new->y0 = y;
	new->z0 = z;
	new->right = NULL;
	new->left = list;
	if (new->left)
		new->left->right = new;
	return (new);
}

static void		centering(t_dots *coord, int x_size, int y_size)
{
	while (coord)
	{
		coord->x -= x_size;
		coord->y -= y_size;
		coord->x0 -= x_size;
		coord->y0 -= y_size;
		coord = coord->right;
	}
}

t_dots			*read_map(int fd)
{
	char	*line;
	char	*line0;
	int		x;
	int		y;
	int		r;
	t_dots	*list;

	list = NULL;
	y = 0;
	while ((r = get_next_line(fd, &line0)))
	{
		if (r < 0)
			exit(-1);
		x = 0;
		line = line0;
		while (*line)
		{
			list = new_element(list, x, y, ft_atoi(line++));
			while (*line && *line != ' ')
				++line;
			++x;
		}
		++y;
		free(line0);
	}
	while (list->left)
		list = list->left;
	centering(list, x / 2, y / 2);
	return (list);
}
