/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:08:44 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/09 21:23:21 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_line	perpendicular_line(double *vector, double *position)
{
	t_line	line;

	line.m = -vector[X] / vector[Y];
	line.b = position[Y] - line.m * position[X];
	return (line);
}

void	rotate_vector(double *origin, double angle)
{
	double	vector[2];
	double	cosangle;
	double	sinangle;

	angle = angle * M_PI / 180;
	cosangle = cos(angle);
	sinangle = sin(angle);
	vector[X] = origin[X];
	vector[Y] = origin[Y];
	origin[X] = vector[X] * cosangle - vector[Y] * sinangle;
	origin[Y] = vector[X] * sinangle + vector[Y] * cosangle;
}

void	update_vector(t_object *object)
{
	int		mouse[2];
	double	distance;

	mouse[X] = 0;
	mouse[Y] = 0;
	mlx_mouse_get_pos(engine()->game.mlx, engine()->game.win,
		&mouse[X], &mouse[Y]);
	distance = mouse[X] - (engine()->map.pixelwidth / 2);
	engine()->map.middle -= mouse[Y] - (engine()->map.pixelheight / 2); 
	if (engine()->map.middle < 0)
		engine()->map.middle = 0;
	if (engine()->map.middle >= engine()->map.pixelheight)
		engine()->map.middle = engine()->map.pixelheight;
	rotate_vector(object->vector, distance / 8);
	rotate_vector(object->sidevector, distance / 8);
	// distance = *on('e') - *on('q');
	// if (distance)
	// {
	// 	rotate_vector(object->vector, distance);
	// 	rotate_vector(object->sidevector, distance);
	// }
	object->cross = perpendicular_line(object->vector,
			(double []){object->x, object->y});
	mlx_mouse_move(engine()->game.mlx, engine()->game.win,
		(engine()->map.pixelwidth / 2), (engine()->map.pixelheight / 2));
}
