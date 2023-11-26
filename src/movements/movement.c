/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:10:21 by lliberal          #+#    #+#             */
/*   Updated: 2023/09/27 11:10:21 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	stoi(double position)
{
	return ((int)(position / SCALE));
}

void	do_nothing(void)
{
	return ;
}

void	object_render_info(t_object *object)
{
	t_render	*render;

	render = &object->render;
	render->distance = object_distance(engine()->player, object);
	(render->distance > 1) || (render->distance = 1);
	render->size[X] = ((double)((SCALE) / render->distance)
			* object->render.max_size[X]);
	render->size[Y] = ((double)((SCALE) / render->distance)
			* object->render.max_size[Y]);
	render->step[X] = (double)render->art->width / render->size[X];
	render->step[Y] = (double)render->art->height / render->size[Y];
	render->screen[X] -= (render->size[X] / 2);
}

void	screen_info_update(t_object *object)
{
	double		x;
	double		y;
	double		rotation[2];
	t_object	*player;

	player = engine()->player;
	x = player->x - object->x;
	y = player->y - object->y;
	rotation[X] = y * -player->vector[X] + x * player->vector[Y];
	rotation[Y] = x * -player->vector[X] - y * player->vector[Y];
	x = (rotation[X] * (double)engine()->map.pixelwidth / rotation[Y])
		+ (double)(engine()->map.pixelwidth / 2.0);
	object->render.on_screen = 0;
	if (rotation[Y] < 0 || x >= engine()->map.pixelwidth || (x) < 0)
		return ;
	object->render.screen[X] = x;
	object->render.screen[Y] = engine()->map.middle;
	object->render.on_screen = 1;
	object_render_info(object);
}

void	object_update(t_object *object)
{
	if (object->move)
		object->move(object);
	if (object->id != PLAYER && object->render.art)
		screen_info_update(object);
	if (object->life < 1)
	{
		list(offstage())->add(object);
		if (object->id == PLAYER)
			end_game("Player died. Game Over\n");
	}
	if (object->update)
		object->update(object);
}
