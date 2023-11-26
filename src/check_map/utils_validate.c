/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:14:54 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 22:13:02 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_elements(t_map *map)
{
	int	index;

	index = -1;
	while (++index < 4)
	{
		printf("%s\n", (char *)map->textures[index]);
	}
}

int	check_rgb(char **arr)
{
	char	**result;
	char	**result2;
	char	**result3;
	int		flag;

	flag = 0;
	if (!arr[0] || !arr[1] || !arr[2] || split_size(arr) != 3)
		return (1);
	result = ft_split(arr[0], ' ');
	result2 = ft_split(arr[1], ' ');
	result3 = ft_split(arr[2], ' ');
	if (split_size(result) > 1 
		|| split_size(result2) > 1 
		|| split_size(result3) > 1)
		flag = 1;
	result = free_matrix(result);
	result2 = free_matrix(result2);
	result3 = free_matrix(result3);
	if (flag == 1)
		return (1);
	return (0);
}

void	elements_counter(t_map *map, int counter)
{
	if ((!map->textures[NO] || !map->textures[SO] 
			|| !map->textures[WE] || !map->textures[EA] 
			|| !map->colors_str[F] || !map->colors_str[C]))
	{
		clean_my_array(map);
		end_game("Check the map's elements");
	}
	if (counter != 6)
		end_game("Map is invalid!");
}

void	clean_my_array(t_map *map)
{
	int	itens;

	itens = -1;
	while (++itens < 5)
		free_null(&map->textures[itens]);
	free_null((void **)&map->colors_str[F]);
	free_null((void **)&map->colors_str[C]);
	end_game("Map error");
}

void	check_array(t_map *map, int	*arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < 7)
	{
		if (i < 5 && arr[i] != 1)
			flag = 1;
		else if (i == 6 && arr[i] != 0)
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		clean_my_array(map);
		end_game("The textures are invalid");
	}
}
