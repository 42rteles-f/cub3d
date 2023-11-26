/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mage.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:46:34 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 19:19:16 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_object	*new_mage(double x, double y)
{
	t_object	*object;

	object = new_enemy(x, y);
	object->id = MAGE;
	object->damage = 1;
	object->alliance = EVIL;
	object->attack = (t_skill){2000, 0, (void *)new_power};
	object->animation = (t_skill){100, 0, NULL, 0};
	object->update = update_sprite;
	object->render.art = *sprites(MAGE);
	object->move = (void *)seek_and_destroy;
	object->spell = *sprites(MAGE_SPELL);
	return (object);
}
