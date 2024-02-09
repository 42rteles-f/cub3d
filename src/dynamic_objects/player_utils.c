/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:44:30 by lliberal          #+#    #+#             */
/*   Updated: 2024/02/09 18:27:53 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	position_start_vector(t_object *player)
{
	char	id;

	id = engine()->map.map[stoi(player->y)][stoi(player->x)];
	if (id == 'N')
	{
		player->vector[X] = 0;
		player->vector[Y] = -1;
	}
	else if (id == 'S')
	{
		player->vector[X] = 0;
		player->vector[Y] = 1;
	}
	else if (id == 'W')
	{
		player->vector[X] = -1;
		player->vector[Y] = 0;
	}
	else
	{
		player->vector[X] = 1;
		player->vector[Y] = 0;
	}
}

t_object	*new_patrono(t_object *holder)
{
	t_object	*patrono;

	patrono = ft_calloc(sizeof(t_object), 1);
	patrono->id = PATRONO;
	patrono->alliance = holder->alliance;
	patrono->life = 1;
	patrono->space = SCALE;
	patrono->x = holder->x + holder->vector[X] * SCALE / 2;
	patrono->y = holder->y + holder->vector[Y] * SCALE / 2;
	patrono->render.art = *sprites(PATRONO);
	patrono->render.max_size[X] = engine()->map.pixelwidth / 1.5;
	patrono->render.max_size[Y] = engine()->map.pixelheight / 1.5;
	patrono->destroy = (void *)free_map_remove;
	patrono->end = (t_skill){5000, engine()->time};
	patrono->collide = patrono_block;
	patrono->move = surround_collision;
	patrono->animation = (t_skill){100, 0};
	patrono->update = patrono_update;
	return (patrono);
}

void	player_move(t_object *object)
{
	double	try[2];

	square_collision(object, (*on(W) - *on(S)) * 2, (*on(D) - *on(A)));
}
