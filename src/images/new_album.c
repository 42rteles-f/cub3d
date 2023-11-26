/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_album.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:35:23 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:50:52 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_variables(t_collect **album, t_image **sprite,
	int *index, void **img)
{
	*album = new_collection();
	*img = (void *)1;
	*index = 0;
	*sprite = (void *)1;
}

void	check_condition(t_image **sprite, void **image,
	char *fullpath, t_type id)
{
	if (*sprite == (void *)1)
	{
		*sprite = new_sprite(fullpath, id);
		*image = (*sprite)->img;
	}
	else
		*image = mlx_xpm_file_to_image(engine()->game.mlx, fullpath,
				&(*sprite)->width, &(*sprite)->height);
}

t_image	*new_album(char *path, t_type id)
{
	t_collect	*album;
	t_image		*sprite;
	void		*image;
	char		*fullpath;
	int			index;

	init_variables(&album, &sprite, &index, &image);
	while (image && sprite)
	{
		fullpath = ft_strjoin(path, sttc_itoa(index++));
		ft_stradd(&fullpath, ".xpm");
		check_condition(&sprite, &image, fullpath, id);
		free(fullpath);
		collection_add(album, image);
	}
	(sprite) && (sprite->album = album->array) && (free_null((void *)&album));
	if (!sprite)
		collection_destroy(album);
	return (sprite);
}
