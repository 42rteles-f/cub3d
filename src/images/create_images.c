/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:45:02 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:35:06 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*search_list(t_list *list, t_type find)
{
	t_list	*node;

	node = list;
	while (node)
	{
		if (((t_object *)node->content)->id == find)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

void	**sprites(t_type find)
{
	static void	*head;
	static void	*found;

	if (find == HEAD)
		return (&head);
	found = search_list(head, find);
	return (&found);
}

void	init_images(void)
{
	(list(sprites(HEAD)))->add(new_sprite(
		"textures/dementor2.xpm", DEMENTOR));
	(list(sprites(HEAD)))->add(new_sprite(
		"textures/lock.xpm", DOOR));
	(list(sprites(HEAD)))->add(new_sprite(
		"textures/smoke.xpm", DEMENTOR_SPELL));
	(list(sprites(HEAD)))->add(new_album(
		"textures/green-spell/green", MAGE_SPELL));
	(list(sprites(HEAD)))->add(new_album(
		"textures/redspell/red", P_SPELL));
	(list(sprites(HEAD)))->add(new_album(
		"textures/patrono/patrono", PATRONO));
	(list(sprites(HEAD)))->add(new_album(
		"textures/wizard-walk/snape", MAGE));
}

t_image	*new_sprite(char *path, t_type id)
{
	t_image	*image;

	image = ft_calloc(sizeof(t_image), 1);
	image->id = id;
	image->img = mlx_xpm_file_to_image(engine()->game.mlx, path,
			&image->width, &image->height);
	if (!image->img)
	{
		free(image);
		return (NULL);
	}
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return (image);
}
		// printf("%s, %i\n", fullpath, !!(image));
