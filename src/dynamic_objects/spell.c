/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:50:24 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 17:50:24 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	power_move(t_object *object)
{
	if (square_collision(object, 3, 0))
		list(offstage())->add(object);
	surround_collision(object);
}

void	power_collide(t_object *object, t_object *target)
{
	if (target->vulnerable && object->alliance != target->alliance)
	{
		list(offstage())->add(object);
		if (target->vulnerable)
			target->life -= object->damage;
		if (target->id == PLAYER)
			printf("Player life: %f\n", target->life);
	}
}

void	free_map_remove(t_object *object)
{
	obj_stack_remove(matrix()->element(stoi(object->x), \
		stoi(object->y)), object);
	free(object);
}

t_object	*new_power(t_object *holder)
{
	t_object	*power;

	power = ft_calloc(sizeof(t_object), 1);
	power->id = SPELL + holder->id;
	power->damage = holder->damage;
	power->alliance = holder->alliance;
	power->life = 1;
	power->space = SCALE / 5;
	power->vector[X] = holder->vector[X];
	power->vector[Y] = holder->vector[Y];
	power->x = holder->x + power->vector[X] * SCALE / 2;
	power->y = holder->y + power->vector[Y] * SCALE / 2;
	power->move = power_move;
	power->render.art = holder->spell;
	power->render.max_size[X] = engine()->map.pixelwidth / 4;
	power->render.max_size[Y] = engine()->map.pixelheight / 4;
	power->destroy = (void *)free_map_remove;
	power->animation = (t_skill){10, 0};
	power->update = update_sprite;
	power->collide = power_collide;
	return (power);
}

void	release_power(t_object *holder)
{
	list(onstage())->add(new_power(holder));
}
