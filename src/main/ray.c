/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:13:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:58:01 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	raycast(t_ray *ray, double *pos, int x, int y)
{
	double		firststep;
	double		increment[2];

	if (!ray->vector[x])
		return ;
	increment[x] = (ray->vector[x] >= 0) - (ray->vector[x] < 0);
	increment[y] = ray->vector[y] / ray->vector[x];
	firststep = (int)(pos[x] + 1 * (ray->vector[x] > 0)) - pos[x];
	pos[x] += firststep - (ray->vector[x] < 0) * 0.000000001;
	pos[y] += firststep * increment[y];
	increment[y] *= increment[x];
	while (matrix()->element(pos[X], pos[Y])->id == 0)
	{
		pos[x] += increment[x];
		pos[y] += increment[y];
	}
	ray->hit[x].point[X] = pos[X] * SCALE;
	ray->hit[x].point[Y] = pos[Y] * SCALE;
	ray->hit[x].wall = x + x + (increment[x] < 0);
}

void	spread_ray(t_object *object, double *interval)
{
	t_ray	ray;
	double	pos[2];

	pos[X] = object->x / SCALE;
	pos[Y] = object->y / SCALE;
	set_ray(&ray, object, interval);
	while (ray.column < interval[1])
	{
		ray.cast(&ray, (double []){pos[X], pos[Y]}, X, Y);
		ray.cast(&ray, (double []){pos[X], pos[Y]}, Y, X);
		ray.closest(&ray, object);
		ray.print(&ray, object);
		ray.rotate(&ray);
	}
}

void	raycast_split(t_object *object)
{
	int		i;
	int		increment;
	double	interval[THREADS][2];

	increment = engine()->map.pixelwidth / THREADS;
	i = 0;
	while (i < THREADS)
	{
		interval[i][0] = i * increment;
		interval[i][1] = (i + 1) * increment;
		(threads())->deploy((t_task){
			spread_ray,
			object,
			(void *)interval[i]});
		i++;
	}
	threads()->wait();
}
