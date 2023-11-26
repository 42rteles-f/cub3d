/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:17:40 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:17:40 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	collection_destroy(t_collect *sequence)
{
	if (sequence && sequence->array)
	{
		free(sequence->array);
		free(sequence);
	}
}

void	collection_clear(t_collect *sequence)
{
	int	index;

	index = 0;
	while (index < sequence->index)
		sequence->array[index++] = NULL;
	sequence->index = 0;
}

void	collection_add(t_collect *sequence, void *element)
{
	void	**array;
	int		i;

	if (!element)
		return ;
	if (sequence->index >= sequence->size - 1)
	{
		array = ft_calloc(sizeof(void *), sequence->size + 50);
		i = 0;
		while (i < sequence->size)
		{
			array[i] = sequence->array[i];
			i++;
		}
		free(sequence->array);
		sequence->array = array;
		sequence->size += 50;
	}
	sequence->array[sequence->index] = element;
	sequence->index++;
}

t_collect	*new_collection(void)
{
	t_collect	*array;

	array = ft_calloc(sizeof(t_collect), 1);
	array->array = ft_calloc(sizeof(void *), 50);
	array->size = 50;
	return (array);
}
