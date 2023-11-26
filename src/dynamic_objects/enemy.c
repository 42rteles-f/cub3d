/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:26:48 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/06 18:26:48 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	throw_skill(t_object *object, t_skill *skill)
{
	if (engine()->time - skill->last > skill->cooldown)
	{
		skill->last = engine()->time;
		list(onstage())->add(skill->new(object));
		return (1);
	}
	return (0);
}

void	seek_and_destroy(t_object *object, t_object *target)
{
	double	distance;

	target = engine()->player;
	object->vector[X] = target->x - object->x;
	object->vector[Y] = target->y - object->y;
	distance = sqrt(object->vector[X] * object->vector[X]
			+ object->vector[Y] * object->vector[Y]);
	object->vector[X] = object->vector[X] / distance;
	object->vector[Y] = object->vector[Y] / distance;
	object->sidevector[X] = object->vector[X];
	object->sidevector[Y] = object->vector[Y];
	rotate_vector(object->sidevector, 90);
	if (object->id == DEMENTOR
		&& object_distance(object, target) > SCALE * 4)
		(!square_collision(object, 0.5, 0))
			|| (square_collision(object, -1, 0));
	else
	{
		if (square_collision(object, 0, 0.5 * object->direction))
			(object->direction *= -1)
				&& (square_collision(object, 0, 1 * object->direction));
	}
	if (object->id == MAGE)
		throw_skill(object, &object->attack);
}

void	dementor_attack(t_object *object)
{
	if (object_distance(object, engine()->player) < SCALE * 4.5)
		throw_skill(object, &object->attack);
}

t_object	*new_enemy(double x, double y)
{
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	object->id = DEMENTOR;
	object->alliance = EVIL;
	object->vulnerable = 1;
	object->damage = 0.05;
	object->direction = 1;
	object->life = 5;
	object->attack = (t_skill){50, 0, (void *)new_power};
	object->space = SCALE / 4;
	object->x = x;
	object->y = y;
	object->vector[X] = 0.01;
	object->vector[Y] = 0;
	object->spell = *sprites(DEMENTOR_SPELL);
	object->destroy = free_map_remove;
	object->move = (void *)seek_and_destroy;
	object->update = (void *)dementor_attack;
	object->render.art = *sprites(DEMENTOR);
	object->render.max_size[X] = engine()->map.pixelwidth / 1.5;
	object->render.max_size[Y] = engine()->map.pixelheight / 1.5;
	return (object);
}
