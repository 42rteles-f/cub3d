/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_usual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:21:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 18:19:08 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	*ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
	return (s);
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

char	**free_matrix(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
	return (NULL);
}

char	**clone_matrix(t_map *map)
{
	char	**new_arr;
	int		i;

	new_arr = ft_calloc(map->height + 1, sizeof(char *));
	i = -1;
	while (map->map[++i])
		new_arr[i] = ft_strdup(map->map[i]);
	return (new_arr);
}
