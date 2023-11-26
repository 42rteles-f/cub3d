/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:24:31 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 19:19:22 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	open_close(t_object *obj, t_object *target)
{
	t_type	*id;

	if (target->id == W_SPELL || target->id == D_SPELL)
	{
		list(offstage())->add(target);
		if (target->id == D_SPELL)
		{
			id = &(matrix()->element(stoi(obj->x), stoi(obj->y))->id);
			if (*id == DOOR)
			{
				*id = FLOOR;
				if (obj->active.cooldown)
				{
					obj->active.cooldown = 0;
					list(onstage())->add(obj->active.new());
				}
			}
			else
				*id = DOOR;
		}
	}
}

t_object	*new_door(double x, double y)
{
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	object->id = DOOR;
	object->life = 1;
	object->space = SCALE;
	object->x = x;
	object->y = y;
	(matrix())->element(stoi(x), stoi(y))->id = DOOR;
	object->vector[X] = 0.01;
	object->vector[Y] = 0;
	object->collide = open_close;
	object->update = surround_collision;
	object->render.art = *sprites(DOOR);
	object->render.max_size[X] = engine()->map.pixelwidth / 8;
	object->render.max_size[Y] = engine()->map.pixelheight / 8;
	object->destroy = free_map_remove;
	return (object);
}
