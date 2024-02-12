/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:54:53 by rteles-f          #+#    #+#             */
/*   Updated: 2024/02/12 23:18:04 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	release_dementor(t_object *event, int *pos)
{
	int	x;

	x = -5;
	while (x < 5)
	{
		if (matrix()->element(pos[X] + x, pos[Y] - 4)->id == 0)
		{
			list(onstage())->add(new_enemy(
				(pos[X] + x) * SCALE, (pos[Y] - 4) * SCALE));
			event->active.index--;
			break ;
		}
		x++;
	}
}

void	release_mage(t_object *event, int *pos)
{
	int	x;

	x = -5;
	while (x < 5)
	{
		if (matrix()->element(pos[X] + x, pos[Y] + 5)->id == 0)
		{
			list(onstage())->add(new_mage(
				(pos[X] + x) * SCALE, (pos[Y] + 5) * SCALE));
			event->active.index--;
			break ;
		}
		x++;
	}
}

void	drop_wave_enemy(t_object *event)
{
	int	pos[2];

	if (event->active.index <= 0)
	{
		list(offstage())->add(event);
		return ;
	}
	if (engine()->time - event->active.last < event->active.cooldown)
		return ;
	event->active.last = engine()->time;
	pos[X] = stoi(engine()->player->x);
	pos[Y] = stoi(engine()->player->y);
	release_dementor(event, pos);
	release_mage(event, pos);
}

t_object	*start_wave(void)
{
	t_object	*event;

	event = new_door(engine()->player->x, engine()->player->y);
	event->id = DOOR;
	event->render.art = NULL;
	(matrix())->element(stoi(event->x), stoi(event->y))->id = FLOOR;
	event->active = (t_skill){2000, 0, NULL, 50};
	event->update = drop_wave_enemy;
	return (event);
}

t_object	*new_event(double x, double y)
{
	t_object	*event;

	event = new_door(x, y);
	event->id = DOOR;
	event->active = (t_skill){1, 0, (void *)start_wave};
	return (event);
}
