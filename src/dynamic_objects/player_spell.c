/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:51:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 17:52:40 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	patrono_block(t_object *object, t_object *target)
{
	if (target->id == DEMENTOR_SPELL && object->alliance != target->alliance)
		list(offstage())->add(target);
}

void	end_spell(t_object *block)
{
	if (engine()->time - block->end.last > block->end.cooldown)
	{
		list(offstage())->add(block);
		engine()->player->vulnerable = 1;
		engine()->player->collide = (void *)do_nothing;
		engine()->player->space = SCALE / 4;
	}
	else
		surround_collision(engine()->player);
}

void	patrono_update(t_object *object)
{
	t_list		*node;
	t_object	*element;

	node = *onstage();
	while (node)
	{
		element = node->content;
		if (element->id == DEMENTOR)
			square_collision(element, -1, 0);
		node = node->next;
	}
	end_spell(object);
}

t_object	*new_block_spell(t_object *holder)
{
	t_object	*block;

	block = ft_calloc(sizeof(t_object), 1);
	block->id = SPELL + holder->id;
	block->x = holder->x;
	block->y = holder->y;
	holder->vulnerable = 0;
	holder->space = SCALE / 2;
	holder->collide = catch_spells;
	block->end = (t_skill){500, engine()->time};
	block->update = end_spell;
	block->life = 1;
	block->destroy = (void *)free_map_remove;
	return (block);
}

t_object	*new_wall_spell(t_object *holder)
{
	t_object	*wall;

	wall = ft_calloc(sizeof(t_object), 1);
	wall->id = SPELL + DOOR * *on(49) + WALL * *on(50);
	wall->active = (t_skill){5000, 0};
	wall->life = 1;
	wall->vector[X] = holder->vector[X];
	wall->vector[Y] = holder->vector[Y];
	wall->x = holder->x + wall->vector[X] * SCALE / 2;
	wall->y = holder->y + wall->vector[Y] * SCALE / 2;
	wall->update = create_wall;
	wall->destroy = (void *)free_map_remove;
	obj_stack_add(matrix()->element(stoi(wall->x), stoi(wall->y)), wall);
	return (wall);
}
