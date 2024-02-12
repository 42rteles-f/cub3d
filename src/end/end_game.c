/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:51:53 by lliberal          #+#    #+#             */
/*   Updated: 2024/02/12 23:17:48 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*free_null(void **mem)
{
	if (!mem)
		return (NULL);
	if (*mem)
		free(*mem);
	*mem = NULL;
	return (NULL);
}

void	free_textures_colors(void)
{
	int		index;
	t_image	**album;

	album = (t_image **)engine()->map.textures;
	index = -1;
	while (++index < 5)
	{
		if (album[index] != NULL)
		{
			mlx_destroy_image(engine()->game.mlx, album[index]->img);
			free(album[index]);
		}
		album[index] = NULL;
	}
}

void	destroy_album(void **album)
{
	int	i;

	if (!album || !*album)
		return ;
	i = 0;
	while (album[i])
	{
		mlx_destroy_image(engine()->game.mlx, album[i]);
		i++;
	}
	free(album);
}

void	clear_sprites(t_list **list)
{
	t_list	*node;
	t_list	*hold;
	t_image	*sprite;

	node = *list;
	while (node)
	{
		sprite = (t_image *)node->content;
		if (sprite->id == WALL)
			;
		else if (sprite->album)
			destroy_album(sprite->album);
		else
			mlx_destroy_image(engine()->game.mlx, sprite->img);
		free(sprite);
		hold = node->next;
		free(node);
		node = hold;
	}
	*list = NULL;
}

void	end_game(char *message)
{
	(message) && (write(2, message, ft_strlen(message))) && (write(2, "\n", 1));
	threads()->end();
	list(offstage())->forEach(remove_from_list, onstage());
	list(offstage())->destroy();
	list(onstage())->destroy();
	collection_destroy(engine()->on_screen);
	matrix()->destroy();
	engine()->map.copy = free_matrix(engine()->map.copy);
	engine()->map.map = free_matrix(engine()->map.map);
	clear_sprites((t_list **)sprites(HEAD));
	free_textures_colors();
	if (engine()->game.canvas.img)
		mlx_destroy_image(engine()->game.mlx, engine()->game.canvas.img);
	if (engine()->game.win)
		mlx_destroy_window(engine()->game.mlx, engine()->game.win);
	if (engine()->game.mlx)
	{
		mlx_destroy_display(engine()->game.mlx);
		mlx_loop_end(engine()->game.mlx);
		free(engine()->game.mlx);
	}
	sleep(1);
	exit(0);
}
