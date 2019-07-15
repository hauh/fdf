/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:40:45 by smorty            #+#    #+#             */
/*   Updated: 2019/07/15 22:28:25 by smorty           ###   ########.fr       */
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

t_dots			*read_map(int fd, double *scale)
{
	t_dots	*list;
	char	*line;
	char	**split;
	int		coord[2];
	int		i;

	list = NULL;
	coord[Y] = 0;
	while ((i = get_next_line(fd, &line)))
	{
		if (i < 0 || !(split = ft_strsplit((const char *)line, ' ')))
			exit(-1);
		coord[X] = 0;
		while (*split)
			list = new_element(list, coord[X]++, coord[Y], ft_atoi(*split++));
		i = coord[X];
		while (i--)
			free(*--split);
		++coord[Y];
		free(split);
		free(line);
	}
	if (list)
	{
		list->x0 -= coord[X] / 2;
		list->y0 -= coord[Y] / 2;
		while (list->left)
		{
			list = list->left;
			list->x0 -= coord[X] / 2;
			list->y0 -= coord[Y] / 2;
		}
		down_linking(list);
		*scale = cbrt((FDF_HEIGHT * FDF_WIDTH) / (coord[X] * coord[Y]));
	}
	return (list);
}
