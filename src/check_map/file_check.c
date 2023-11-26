/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:53:58 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 17:08:46 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_file(t_map *map, char *name)
{
	int	file;

	(void)map;
	file = ft_strlen(name);
	if (file <= 4 || ft_strncmp(&name[file - 4], ".cub", 10))
		end_game("Invalid File Name.");
	file = open(name, O_RDONLY);
	if (file < 0)
		end_game("Problem openning file.");
	map->map = filetomatrix(NULL, 0, file);
	close(file);
	if (!map->map || !*map->map || !**map->map)
		end_game("Invalid Map.");
}

void	file_tomap(t_map *map)
{
	int		replace;
	int		counter;

	replace = 0;
	while (map->map[replace + 6])
	{
		free(map->map[replace]);
		map->map[replace] = map->map[replace + 6];
		map->map[replace + 6] = NULL;
		replace++;
	}
}

void	larger_line(t_map *map)
{
	int	i;
	int	length;
	int	keep;

	keep = 0;
	i = 0;
	while (map->map[i])
	{
		length = ft_strlen(map->map[i]);
		if (length > keep)
			keep = length;
		i++;
	}
	map->width = keep;
	map->height = i - 1;
}

void	get_dimensions(t_map *map)
{
	larger_line(map);
	map->size = map->width * map->height;
}

void	add_border(t_map *map)
{
	int		i;
	int		letter;
	int		height;

	height = 0;
	map->copy = ft_calloc(sizeof(char *), split_size(map->map) + 1 + 2);
	map->copy[height++] = allocate_and_fill(map->width + 1, ' ');
	i = 0;
	while (map->map[i])
	{
		map->copy[height] = allocate_and_fill(map->width + 1, ' ');
		letter = -1;
		while (map->map[i][++letter])
		{
			if (map->map[i][letter] != '\n')
				map->copy[height][letter + 1] = map->map[i][letter];
		}
		i++;
		height++;
	}
	map->copy[height++] = allocate_and_fill(map->width + 1, ' ');
	map->player_posx++;
	map->player_posy++;
}
