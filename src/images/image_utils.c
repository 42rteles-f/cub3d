/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:25:46 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:27:55 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	(void)dst;
	if (color == (int)0xFF000000)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_image *art, int x, int y)
{
	char	*dst;

	dst = art->addr + (y * art->line_length + x * (art->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}
