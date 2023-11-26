/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:12:32 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:12:32 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_object	*matrix_get_position(int x, int y)
{
	t_array	*array;

	array = &((t_fullmatrix *)matrix())->this;
	if (x < array->length && x > 0
		&& y < array->height && y > 0)
		return (&array->array[x + y * array->length]);
	return (&array->invalid);
}

static void	matrix_foreach(void (*apply)())
{
	int		i;
	t_array	*this;

	this = &((t_fullmatrix *)matrix())->this;
	i = 0;
	while (i < this->size)
	{
		apply(&this->array[i], i);
		i++;
	}
}

static t_matrix	*create_object_array(char **map)
{
	t_array	*this;

	this = &((t_fullmatrix *)matrix())->this;
	this->height = 0;
	while (map[this->height])
		this->height++;
	this->length = bigger_line(map);
	this->size = this->length * this->height;
	this->array = ft_calloc(sizeof(t_object), this->size);
	this->invalid.id = -1;
	return (matrix());
}

static void	destroy_matrix(void)
{
	t_array	*this;

	this = &((t_fullmatrix *)matrix())->this;
	if (!this->array)
		return ;
	free(this->array);
	ft_bzero(this, sizeof(t_array));
}

inline t_matrix	*matrix(void)
{
	static t_fullmatrix	matrix = {
		matrix_get_position,
		matrix_foreach,
		create_object_array,
		destroy_matrix,
	};

	return ((t_matrix *)&matrix);
}
