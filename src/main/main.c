/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:05:15 by lliberal          #+#    #+#             */
/*   Updated: 2023/09/13 15:05:15 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update(t_engine *engine)
{
	static double	newtime;

	engine->time = get_time();
	if (engine->time - newtime > 8)
	{
		newtime = engine->time;
		(threads())->deploy((t_task){(void *)mlx_put_image_to_window,
			engine->game.mlx, engine->game.win, engine->game.canvas.img, 0, 0});
		collection_clear(engine->on_screen);
		list(onstage())->forEach(object_update);
		(list(offstage()))->forEach(remove_from_list, onstage());
		list(offstage())->destroy();
		(list(onstage()))->forEach(on_screen_add, engine->on_screen);
		ft_bubble_sort((t_render **)engine->on_screen->array,
			engine->on_screen->index);
		threads()->wait();
		raycast_split(engine->player);
		if (engine->minimap)
			engine->minimap();
		update_vector(engine->player);
	}
}

void	init_hooks(t_gui *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_down, engine());
	mlx_hook(game->win, 3, 1L << 1, key_up, engine());
	mlx_hook(game->win, 17, 1L << 17, (void *)end_game, NULL);
	mlx_mouse_hook(game->win, (void *)mouse_action, engine());
	mlx_loop_hook(game->mlx, (void *)update, engine());
}

void	init_graphic_interface(t_gui *game, t_map *map)
{
	map->pixelheight = 720;
	map->pixelwidth = 1080;
	map->middle = map->pixelheight / 2;
	game->win = mlx_new_window(game->mlx,
			map->pixelwidth, map->pixelheight, "cub3d!");
	game->canvas.img = mlx_new_image(game->mlx,
			map->pixelwidth, map->pixelheight);
	game->canvas.addr = mlx_get_data_addr(game->canvas.img,
			&game->canvas.bits_per_pixel, &game->canvas.line_length,
			&game->canvas.endian);
}

void	game_setup(t_engine *engine, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	if (argc != 2)
		end_game("Usage: ./cub3d [map_path.cub]\n");
	validate_map(&engine->map, argv[1]);
	init_graphic_interface(&engine->game, &engine->map);
	init_hooks(&engine->game);
	init_images();
	matrix()->create(engine->map.map)->forEach(setdefaultobject);
	engine->on_screen = new_collection();
	threads()->start();
}

int	main(int argc, char **argv)
{
	game_setup(engine(), argc, argv);
	mlx_loop(engine()->game.mlx);
	return (0);
}
