/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:54:54 by lliberal          #+#    #+#             */
/*   Updated: 2023/09/26 17:54:54 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	object_distance(t_object *first, t_object *second)
{
	double	x;
	double	y;

	x = first->x - second->x;
	y = first->y - second->y;
	return (sqrt(x * x + y * y));
}

void	on_screen_add(t_object *object, t_collect *collect)
{
	if (object->render.on_screen)
		collection_add(collect, &object->render);
}

void	create_dinamyc_object(t_object *object)
{
	char		id;

	id = engine()->map.map[(int)object->y][(int)object->x];
	if (id && ft_strchr("NSWE", id))
	{
		(engine())->player = new_player((int)object->x * SCALE + SCALE / 2,
				(int)object->y * SCALE + SCALE / 2);
		list(onstage())->add(engine()->player);
	}
	else if (id == 'D')
		list(onstage())->add(new_door(object->x * SCALE + SCALE / 2,
			object->y * SCALE + SCALE / 2));
	else if (id == 'A')
		list(onstage())->add(new_event(object->x * SCALE + SCALE / 2,
			object->y * SCALE + SCALE / 2));
}

void	setdefaultobject(t_object *object, int position)
{
	object->x = position % engine()->map.width;
	object->y = position / engine()->map.width;
	if (object->x < ft_strlen(engine()->map.map[(int)object->y]))
	{
		object->id = (engine()->map.map[(int)object->y][(int)object->x] == '1');
		if (object->id == 0)
			create_dinamyc_object(object);
	}
	else 
		object->id = 0;
}
