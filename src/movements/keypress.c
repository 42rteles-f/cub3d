/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:53:50 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 19:16:55 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*on(int press)
{
	static char	keyboard[70000];

	return (&keyboard[press]);
}

int	key_up(int keycode, t_engine *engine)
{
	(void)engine;
	*on(keycode) = 0;
	return (1);
}

int	key_down(int keycode, t_engine *engine)
{
	*on(keycode) = 1;
	if (keycode == ESC)
		end_game(NULL);
	else if (keycode == SPACE)
		release_power(engine->player);
	else if (keycode == 'm')
		((engine->minimap)
			&& !(engine->minimap = NULL))
			|| (engine->minimap = painting_map);
	else if (keycode == 'p')
	{
		if (!engine->game_on)
			mlx_loop_hook(engine->game.mlx, (void *)do_nothing, engine);
		else
			mlx_loop_hook(engine->game.mlx, (void *)update, engine);
		engine->game_on = !engine->game_on;
	}
	else if (keycode == 49 || keycode == 50 || keycode == 51)
		throw_skill(engine->player, &engine->player->spellbook[keycode - 49]);
	else if (keycode == SHIFT)
		square_collision(engine->player,
			(*on(W) - *on(S)) * SCALE * 1.5, (*on(D) - *on(A)) * SCALE * 1.5);
	return (1);
}
	// else if (keycode == 'q')
	// {
	// 	rotate_vector(engine->player->vector, -3);
	// 	rotate_vector(engine->player->sidevector, -3);
	// }
	// else if (keycode == 'e')
	// {
	// 	rotate_vector(engine->player->vector, 3);
	// 	rotate_vector(engine->player->sidevector, 3);
	// }

void	mouse_action(int key, t_engine *testt)
{
	if (key == 1)
		release_power(engine()->player);
	if (key == 3)
		throw_skill(engine()->player, &engine()->player->block);
}
