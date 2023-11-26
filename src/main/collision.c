/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:32:09 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:32:09 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	obj_stack_remove(t_object *list, t_object *remove)
{
	while (list->on_top && (list->on_top != remove))
		list = list->on_top;
	if (list->on_top == remove)
		list->on_top = remove->on_top;
	remove->on_top = NULL;
}

void	obj_stack_add(t_object *list, t_object *add)
{
	if (!list || !add)
		return ;
	while (list->on_top)
		list = list->on_top;
	list->on_top = add;
}

void	list_interact(t_object *object, t_object *list)
{
	while (list)
	{
		if (object_distance(object, list) > object->space)
			object->collide(object, list);
		list = list->on_top;
	}
}

void	surround_collision(t_object *object)
{
	int			x;
	int			y;
	t_object	*target;

	y = -1;
	while (y < 2)
	{
		x = -1;
		while (x < 2)
		{
			target = matrix()->element(
					stoi(object->x) + x, stoi(object->y) + y)->on_top;
			while (target)
			{
				if (object_distance(object, target) < object->space)
					object->collide(object, target);
				target = target->on_top;
			}
			x++;
		}
		y++;
	}
}

int	square_collision(t_object *object, double straight, double sideway)
{
	double	try[2];

	(sideway && straight) && (sideway *= 0.7) && (straight *= 0.7);
	try[X] = object->x + (straight) * object->vector[X]
		+ (sideway) * object->sidevector[X];
	try[Y] = object->y + (straight) * object->vector[Y]
		+ (sideway) * object->sidevector[Y];
	if (stoi(try[X]) != stoi(object->x) || stoi(try[Y]) != stoi(object->y))
	{
		obj_stack_remove(matrix()->element(
				stoi(object->x), stoi(object->y)), object);
		if (matrix()->element(stoi(try[X]), stoi(object->y))->id == 0)
			object->x = try[X];
		if (matrix()->element(stoi(object->x), stoi(try[Y]))->id == 0)
			object->y = try[Y];
		obj_stack_add(matrix()->element(
				stoi(object->x), stoi(object->y)), object);
	}
	else
	{
		object->x = try[X];
		object->y = try[Y];
	}
	return (matrix()->element(stoi(try[X]), stoi(try[Y]))->id);
}
