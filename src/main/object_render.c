/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:35:08 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:35:08 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	paint_sprite_column(t_ray *ray, t_render *object)
{
	int		index;
	t_image	*img;
	double	sprite[2];
	double	vari;

	if (ray->column < object->screen[X]
		|| ray->column > (object->screen[X] + object->size[X]))
		return ;
	img = &engine()->game.canvas;
	sprite[X] = (ray->column - object->screen[X]) * object->step[X];
	sprite[Y] = (object->art->height / 2);
	index = 0;
	vari = 0;
	while (sprite[Y] + vari < object->art->height)
	{
		if (object->screen[Y] - index >= 0)
			my_mlx_pixel_put(img, ray->column, object->screen[Y] - index,
				my_mlx_pixel_get(object->art, sprite[X], sprite[Y] - vari));
		if (object->screen[Y] + index < engine()->map.pixelheight)
			my_mlx_pixel_put(img, ray->column, object->screen[Y] + index,
				my_mlx_pixel_get(object->art, sprite[X], sprite[Y] + vari));
		vari += object->step[Y];
		index++;
	}
}

void	paint_objects_column(t_ray *ray, t_object *wall)
{
	int			index;
	int			height;
	t_collect	*array;
	t_render	**objects;

	array = ray->on_screen;
	objects = (t_render **)ray->on_screen->array;
	index = 0;
	while (index < array->index)
	{
		if (ray->distance > objects[index]->distance)
		{
			print_wall(ray);
			ray->distance = -1;
		}
		paint_sprite_column(ray, objects[index]);
		index++;
	}
	if (ray->distance > 0)
		print_wall(ray);
}
