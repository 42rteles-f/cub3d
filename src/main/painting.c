/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:12:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 18:41:06 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	paint_block(t_image *data, double x, double y, int color)
{
	int	i;
	int	j;
	int	limit;

	limit = SCALE / 2;
	x *= limit;
	y *= limit;
	i = 0;
	while (i < limit)
	{
		j = 0;
		while (j < limit)
		{
			my_mlx_pixel_put(&engine()->game.canvas, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	print_line(double x, double y, double *vector)
{
	while (matrix()->element(stoi(x), stoi(y))->id == 0)
	{
		my_mlx_pixel_put(&engine()->game.canvas, x / 2, y / 2, 0xFF0000);
		x += vector[X];
		y += vector[Y];
	}
}

void	print_formula(double x, double y, t_line *line)
{
	int	counter;

	counter = -25;
	while (counter < 50)
	{
		y = (x + counter) * line->m + line->b;
		if (valid_position((x + counter) / 2, engine()->map.pixelwidth)
			&& valid_position(y / 2, engine()->map.pixelheight))
			my_mlx_pixel_put(&engine()->game.canvas, (x + counter) / 2, \
				y / 2, 0xFF0000);
		counter++;
	}
}

void	flying_objects(void)
{
	t_list		*node;
	t_object	*object;

	node = *onstage();
	while (node)
	{
		object = (t_object *)node->content;
		paint_block(&engine()->game.canvas, (object->x) / SCALE, \
			(object->y) / SCALE, 0xFF0000);
		node = node->next;
	}
}

void	painting_map(void)
{
	double		i[2];
	t_map		*map;
	t_object	*player;

	map = &engine()->map;
	i[1] = -1;
	while (++i[1] < (map->height + 1))
	{
		i[0] = -1;
		while (++i[0] < map->width)
		{
			if (matrix()->element(i[0], i[1])->id == 1)
				paint_block(&engine()->game.canvas, i[0], i[1], 0x000000);
			else
				paint_block(&engine()->game.canvas, i[0], i[1], 0xFFD700);
		}
	}
	player = engine()->player;
	i[X] = player->vector[X];
	i[Y] = player->vector[Y];
	rotate_vector(i, -35);
	print_line(player->x, player->y, i);
	rotate_vector(i, +70);
	print_line(player->x, player->y, i);
	flying_objects();
}
