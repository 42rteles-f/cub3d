/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:24:47 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:28:08 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	painting_ceiling_floor(t_ray *ray, double height, double middle)
{
	int	index;
	int	floor;
	int	ceiling;

	index = height;
	floor = engine()->map.colors[F];
	ceiling = engine()->map.colors[C];
	while (index < engine()->map.pixelheight)
	{
		if (middle - index > 0)
			my_mlx_pixel_put(&engine()->game.canvas, ray->column,
				middle - index, ceiling);
		if (middle + index < engine()->map.pixelheight)
			my_mlx_pixel_put(&engine()->game.canvas, ray->column,
				middle + index, floor);
		index++;
	}
}

t_image	*give_wall_sprite(t_ray *ray)
{
	t_image		*wall;

	if (matrix()->element(
			stoi(ray->hit->point[X]), stoi(ray->hit->point[Y]))->id == DOOR)
		wall = (((t_image *)*sprites(WALL))->album)[DOOR];
	else
		wall = (((t_image *)*sprites(WALL))->album)[ray->hit->wall];
	return (wall);
}

void	set_wall(t_render *wall, t_ray *ray)
{
	wall->art = give_wall_sprite(ray);
	(ray->distance > 1) || (ray->distance = 1);
	wall->height = ((double)((SCALE) / ray->distance)
			* (engine()->map.pixelheight));
	((ray->hit->wall < 2)
		&& (wall->width = ray->hit->point[Y] / SCALE
			- (int)(ray->hit->point[Y] / SCALE))
		|| (wall->width = ray->hit->point[X] / SCALE
			- (int)(ray->hit->point[X] / SCALE)));
	wall->width *= wall->art->width;
	wall->step[Y] = wall->art->height / (wall->height);
	(wall->height < (engine()->map.pixelheight * 2))
		|| (wall->height = engine()->map.pixelheight * 2);
	wall->height /= 2;
	wall->size[Y] = engine()->map.pixelheight;
}

void	print_wall(t_ray *ray)
{
	double		middle;
	double		texpos;
	int			index;
	t_image		*image;
	t_render	wall;

	set_wall(&wall, ray);
	image = &engine()->game.canvas;
	texpos = 0;
	index = 0;
	middle = engine()->map.middle;
	while (index <= wall.height)
	{
		if (middle - index >= 0)
			my_mlx_pixel_put(image, ray->column, middle - index,
				my_mlx_pixel_get(wall.art, wall.width,
					(wall.art->height / 2) - texpos));
		if (middle + index < wall.size[Y])
			my_mlx_pixel_put(image, ray->column, middle + index,
				my_mlx_pixel_get(wall.art, wall.width,
					(wall.art->height / 2) + texpos));
		texpos += wall.step[Y];
		index++;
	}
	painting_ceiling_floor(ray, wall.height, middle);
}
