/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:54:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:58:58 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	list_textures_elements(t_map *map, int counter)
{
	int	index;
	int	i;

	i = -1;
	while (map->map[++i] && i < 6)
	{
		counter++;
		index = not_space(map->map[i]);
		if (ft_strncmp("NO ", &(map->map[i][index]), 3) == 0)
			map->textures[NO] = (void *)ft_strdup(cut_str(&(map->map[i][3])));
		else if (ft_strncmp("SO ", &(map->map[i][index]), 3) == 0)
			map->textures[SO] = (void *)ft_strdup(cut_str(&(map->map[i][3])));
		else if (ft_strncmp("WE ", &(map->map[i][index]), 3) == 0)
			map->textures[WE] = (void *)ft_strdup(cut_str(&(map->map[i][3])));
		else if (ft_strncmp("EA ", &(map->map[i][index]), 3) == 0)
			map->textures[EA] = (void *)ft_strdup(cut_str(&(map->map[i][3])));
		else if (ft_strncmp("F ", &(map->map[i][index]), 2) == 0)
			map->colors_str[F] = (void *)ft_strdup(cut_str(&(map->map[i][2])));
		else if (ft_strncmp("C ", &(map->map[i][index]), 2) == 0)
			map->colors_str[C] = (void *)ft_strdup(cut_str(&(map->map[i][2])));
		else
			clean_my_array(map);
	}
	elements_counter(map, counter);
}

void	alpha_security(t_map *map)
{
	char	**rgbfloor;
	char	**rgbceiling;

	rgbfloor = ft_split((char *)map->colors_str[0], ',');
	rgbceiling = ft_split((char *)map->colors_str[1], ',');
	if (split_size(rgbfloor) != 3 || split_size(rgbceiling) != 3)
	{
		rgbfloor = free_matrix(rgbfloor);
		rgbceiling = free_matrix(rgbceiling);
		clean_my_array(map);
	}
	if (isnumber(rgbfloor[0]) || isnumber(rgbfloor[1]) 
		|| isnumber(rgbfloor[2]) || isnumber(rgbceiling[0])
		|| isnumber(rgbceiling[1]) || isnumber(rgbceiling[2]))
	{
		rgbfloor = free_matrix(rgbfloor);
		rgbceiling = free_matrix(rgbceiling);
		clean_my_array(map);
	}
	rgbfloor = free_matrix(rgbfloor);
	rgbceiling = free_matrix(rgbceiling);
}

void	check_colors(t_map *map, int red, int green, int blue)
{
	char	**rgb;
	int		i[3];

	i[0] = -1;
	i[1] = 0;
	while (++i[0] < 2)
	{
		rgb = ft_split((char *)map->colors_str[i[0]], ',');
		if (check_rgb(rgb) == 1)
			i[1] = 1;
		else
		{
			red = ft_atoi(rgb[0]);
			green = ft_atoi(rgb[1]);
			blue = ft_atoi(rgb[2]);
		}
		rgb = free_matrix(rgb);
		if (limit_rgb(red, green, blue))
			i[1] = 1;
		i[2] = (red << 16) | (green << 8) | blue;
		free(map->colors_str[i[0]]);
		map->colors[i[0]] = i[2];
	}
	if (i[1] == 1)
		end_game("The RGB colors are invalid");
}

void	check_characters(t_map *map)
{
	int		x;
	int		y;

	x = -1;
	while (map && map->map[++x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (!ft_strchr("01NSWEDA\n", map->map[x][y]) 
				&& !ft_isspace(map->map[x][y]))
				end_game("Char not available.");
			if (ft_strchr("NSWE", map->map[x][y]))
			{
				if (map->player_posx != 0 && map->player_posy != 0)
					end_game("Two players is forbidden.");
				map->player_posx = x;
				map->player_posy = y;
			}
			y++;
		}
	}
}

void	check_open_textures(t_map *map)
{
	t_image	*element;
	int		flag;
	int		index;

	index = -1;
	flag = 0;
	while (++index < 4)
	{
		element = new_sprite(map->textures[index], WALL);
		if (!element)
			clean_textures_broken(map, index);
		free(map->textures[index]);
		map->textures[index] = (void *)element;
	}
	element = new_sprite("textures/medievaldoor.xpm", DOOR);
	map->textures[index] = (void *)element;
	element = ft_calloc(sizeof(t_image), 1);
	element->id = WALL;
	element->album = map->textures;
	list((t_list **)sprites(HEAD))->add(element);
}
