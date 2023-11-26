/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:28:45 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:58:14 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	**filetomatrix(char **matrix, int counter, int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
		matrix = ft_calloc(counter + 1, sizeof(char *));
	else
	{
		if (str && (*str == '\n' || empty_string(str)))
			free_null((void *)&str);
		if (str && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = 0;
		matrix = filetomatrix(matrix, counter + (!!str), fd);
	}
	if (matrix && str)
		matrix[counter] = str;
	return (matrix);
}

char	*allocate_and_fill(int size, int value)
{
	void	*new;

	new = ft_calloc(sizeof(char), size + 1);
	ft_memset(new, value, size);
	return (new);
}

void	clean_textures_broken(t_map *map, int counter)
{
	t_image	**album;
	int		index;

	album = (t_image **)engine()->map.textures;
	index = -1;
	while (++index < 4)
	{
		if (index < counter)
		{
			mlx_destroy_image(engine()->game.mlx, album[index]->img);
			free(album[index]);
		}
		else
		{
			free(map->textures[index]);
		}
		album[index] = NULL;
	}
	free_null((void **)&map->colors_str[F]);
	free_null((void **)&map->colors_str[C]);
	end_game("Textures are invalid");
}

void	textures_control(t_map *map)
{
	int	i;
	int	index;
	int	arr[7];

	i = -1;
	ft_bzero(arr, sizeof(int) * 7);
	while (map->map[++i] && i < 6)
	{
		index = not_space(map->map[i]);
		if (ft_strncmp("NO ", &(map->map[i][index]), 3) == 0)
			arr[0]++;
		else if (ft_strncmp("SO ", &(map->map[i][index]), 3) == 0)
			arr[1]++;
		else if (ft_strncmp("WE ", &(map->map[i][index]), 3) == 0)
			arr[2]++;
		else if (ft_strncmp("EA ", &(map->map[i][index]), 3) == 0)
			arr[3]++;
		else if (ft_strncmp("F ", &(map->map[i][index]), 2) == 0)
			arr[4]++;
		else if (ft_strncmp("C ", &(map->map[i][index]), 2) == 0)
			arr[5]++;
		else
			arr[6]++;
	}
	check_array(map, arr);
}

void	validate_map(t_map *map, char *name)
{
	engine()->game.mlx = mlx_init();
	get_file(map, name);
	textures_control(map);
	list_textures_elements(map, 0);
	alpha_security(map);
	check_open_textures(map);
	check_colors(map, 0, 0, 0);
	file_tomap(map);
	check_characters(map);
	get_dimensions(map);
	add_border(map);
	flooding_map(map);
}
