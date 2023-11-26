/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:16:44 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:16:24 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	not_space(char *name)
{
	int	index;

	index = 0;
	while (ft_isspace(name[index]))
		index++;
	return (index);
}

int	isnumber(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ' ')
			return (1);
	}
	return (0);
}

int	empty_string(char *str)
{
	int	i;

	i = 0;
	while (str && ft_isspace(str[i]))
		i++;
	if (!str[i] || str[i] == '\n')
		return (1);
	return (0);
}

void	print_map(t_map *map)
{
	int	index;

	index = -1;
	while (map->map && map->map[++index])
		printf("%s\n", map->map[index]);
}

int	limit_rgb(int red, int green, int blue)
{
	if (red > 255 || green > 255 || blue > 255 
		|| red < 0 || green < 0 || blue < 0)
		return (1);
	return (0);
}
