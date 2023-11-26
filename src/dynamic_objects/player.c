/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:39:29 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 17:39:29 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_sprite(t_object *object)
{
	if (engine()->time - object->animation.last > object->animation.cooldown)
	{
		object->animation.last = engine()->time;
		object->animation.index++;
		if (!object->render.art || !object->render.art->album)
			return ;
		if (!object->render.art->album[object->animation.index])
			object->animation.index = 0;
		object->render.art->img
			= object->render.art->album[object->animation.index];
		object->render.art->addr = mlx_get_data_addr(object->render.art->img,
				&object->render.art->bits_per_pixel,
				&object->render.art->line_length, &object->render.art->endian);
	}
}

void	destroy_wall(t_object *object)
{
	if (engine()->time - object->active.last > object->active.cooldown)
	{
		(matrix())->element(stoi(object->x), stoi(object->y))->id = 0;
		list(offstage())->add(object);
	}
}

void	create_wall(t_object *object)
{
	double	hold[2];

	hold[X] = object->x;
	hold[Y] = object->y;
	if (square_collision(object, 5, 0))
		list(offstage())->add(object);
	else if (stoi(hold[X]) != stoi(object->x) 
		|| stoi(hold[Y]) != stoi(object->y)
		&& (matrix())->element(stoi(object->x), stoi(object->y))->id == 0)
	{
		if (object->id == W_SPELL)
		{
			(matrix())->element(stoi(object->x), stoi(object->y))->id = 1;
			object->active.last = engine()->time;
			object->update = destroy_wall;
		}
		else
			list(offstage())->add(object);
	}
}

void	catch_spells(t_object *object, t_object *target)
{
	if (object->alliance != target->alliance)
		list(offstage())->add(target);
}

t_object	*new_player(double x, double y)
{
	t_object	*object;

	object = ft_calloc(sizeof(t_object), 1);
	object->id = PLAYER;
	object->alliance = GOOD;
	object->life = 20;
	object->damage = 1;
	object->vulnerable = 1;
	object->spellbook[0] = (t_skill){2000, 0, (void *)new_wall_spell};
	object->spellbook[1] = (t_skill){2000, 0, (void *)new_wall_spell};
	object->spellbook[2] = (t_skill){10000, 0, (void *)new_patrono};
	object->block = (t_skill){1000, 0, (void *)new_block_spell};
	object->space = SCALE / 4;
	object->x = x;
	object->y = y;
	position_start_vector(object);
	object->spell = *sprites(P_SPELL);
	object->sidevector[X] = object->vector[X];
	object->sidevector[Y] = object->vector[Y];
	rotate_vector(object->sidevector, 90);
	update_vector(object);
	object->destroy = free_map_remove;
	object->move = player_move;
	object->collide = catch_spells;
	return (object);
}
