/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:40:45 by smorty            #+#    #+#             */
/*   Updated: 2019/07/03 22:55:57 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>
static t_dots	*new_element(t_dots *list, int x, int y, char z)
{
	t_dots *new;

	if (!(new = (t_dots *)malloc(sizeof(t_dots))))
		exit(-1);
	new->x = x;
	new->y = y;
	new->z = z;
	new->right = NULL;
	new->left = list;
	if (new->left)
		new->left->right = new;
	return (new);
}

t_dots			*read_map(int fd)
{
	char	*line;
	char	*line0;
	int		x;
	int		y;
	int		r;
	t_dots	*list;

	y = 0;
	list = NULL;
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
	return (list);
}
