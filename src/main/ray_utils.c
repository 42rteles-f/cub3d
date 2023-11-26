/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:18:31 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:33:41 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_ray(t_ray *ray, t_object *object, double *column)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->on_screen = engine()->on_screen;
	ray->rotate = ray_rotate;
	ray->cast = raycast;
	ray->closest = select_point;
	ray->print = print_wall;
	if (ray->on_screen->index)
		ray->print = paint_objects_column;
	ray->vector[X] = object->vector[X];
	ray->vector[Y] = object->vector[Y];
	set_rotation(ray, ((column[0] * S_ANGLE * 2)
			/ engine()->map.pixelwidth) - (S_ANGLE));
	ray->rotate(ray);
	ray->column = column[0];
	set_rotation(ray, (double)(S_ANGLE * 2)
		/ (double)engine()->map.pixelwidth);
}

	// double	cosin;
	// cosin = cos((ray->angle * M_PI)/ 180);
	// ray->distance = (((ray->hit[X].point[X] - object->x) / ray->vector[X])
	// 	* cosin);
	// ydistance = ((ray->hit[Y].point[Y] - object->y) / ray->vector[Y]
	// 	* cosin);	
void	select_point(t_ray *ray, t_object *object)
{
	double	ydistance;
	double	divide;

	divide = sqrt((object->cross.m * object->cross.m) + 1);
	ray->distance = (fabs((object->cross.m * ray->hit[X].point[X])
				- ray->hit[X].point[Y] + object->cross.b)) / divide;
	ydistance = (fabs((object->cross.m * ray->hit[Y].point[X])
				- ray->hit[Y].point[Y] + object->cross.b)) / divide;
	if (ray->distance > ydistance)
	{
		ray->distance = ydistance;
		ray->hit->point[X] = ray->hit[Y].point[X];
		ray->hit->point[Y] = ray->hit[Y].point[Y];
		ray->hit->wall = ray->hit[Y].wall;
	}
}

void	ray_rotate(t_ray *ray)
{
	ray->hold[X] = ray->vector[X];
	ray->hold[Y] = ray->vector[Y];
	ray->vector[X] = (ray->hold[X] * ray->cos)
		- (ray->hold[Y] * ray->sin);
	ray->vector[Y] = (ray->hold[X] * ray->sin)
		+ (ray->hold[Y] * ray->cos);
	ray->column++;
}

void	set_rotation(t_ray *ray, double angle)
{
	ray->radians = (angle * M_PI) / 180;
	ray->cos = cos(ray->radians);
	ray->sin = sin(ray->radians);
}
