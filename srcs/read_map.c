/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:40:45 by smorty            #+#    #+#             */
/*   Updated: 2019/07/12 23:20:55 by smorty           ###   ########.fr       */
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
	int		x;
	int		y;
	int		i;

	list = NULL;
	y = 0;
	while ((i = get_next_line(fd, &line)))
	{
		if (i < 0 || !(split = ft_strsplit((const char *)line, ' ')))
			exit(-1);
		x = 0;
		while (*split)
			list = new_element(list, x++, y, ft_atoi(*split++));
		i = x;
		while (i--)
			free(*--split);
		++y;
		free(split);
		free(line);
	}
	if (list)
	{
		while (list->left)
			list = list->left;
		centering(list, x / 2, y / 2);
		down_linking(list);
		*scale = sqrt(FDF_WIDTH / x + FDF_HEIGHT / y);
	}
	return (list);
}
