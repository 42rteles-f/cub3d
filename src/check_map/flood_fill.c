/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:22:25 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:37:50 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1')
		return ;
	if (map[x][y] == ' ' || map[x][y] == '\t')
		end_game("Error in map (FLOOD)\n");
	map[x][y] = '1';
	flood_fill(map, (x + 1), (y));
	flood_fill(map, (x - 1), (y));
	flood_fill(map, (x), (y + 1));
	flood_fill(map, (x), (y - 1));
}

void	flooding_map(t_map *map)
{
	if (map->player_posx == 1 && map->player_posy == 1)
		end_game("Where are you, soldier?");
	flood_fill(map->copy, map->player_posx, map->player_posy);
	map->copy = free_matrix(map->copy);
}
