/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:24:00 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 22:13:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

inline double	valid_position(double position, double limit)
{
	return (position > 0 && position <= limit);
}

int	bigger_line(char **matrix)
{
	int	i;
	int	length;
	int	keep;

	keep = 0;
	i = 0;
	while (matrix[i])
	{
		length = ft_strlen(matrix[i]);
		if (length > keep)
			keep = length;
		i++;
	}
	return (keep);
}
