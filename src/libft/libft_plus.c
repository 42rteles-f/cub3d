/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:01:00 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:16:34 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_stradd(char **original, char *add)
{
	int		i;
	int		j;
	char	*joined;

	if (!original || !(*original) || !add)
		return (NULL);
	joined = ft_calloc(sizeof(char),
			(ft_strlen((*original)) + ft_strlen(add) + 1));
	if (!joined)
		return (NULL);
	i = -1;
	while ((*original)[++i])
		joined[i] = (*original)[i];
	j = -1;
	while (add[++j])
		joined[i + j] = add[j];
	free((*original));
	*original = joined;
	return (joined);
}

void	ft_bubble_sort(t_render **list, int size)
{
	int			i;
	int			swapped;
	t_render	*hold;

	swapped = 1;
	size--;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < size)
		{
			if (list[i]->distance < list[i + 1]->distance)
			{
				hold = list[i];
				list[i] = list[i + 1];
				list[i + 1] = hold;
				swapped = 1;
			}
			i++;
		}
	}
}

char	*sttc_itoa(int number)
{
	static char	to_ascii[12];
	int			index;
	int			sign;

	sign = (number > 0) - (number < 0);
	index = 11;
	while (number || index == 11)
	{
		to_ascii[--index] = (number % 10) * sign + '0';
		number = number / 10;
	}
	if (sign < 0)
		to_ascii[--index] = '-';
	return (&to_ascii[index]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		n;

	if (!s1 && !s2)
		return (NULL);
	str = malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2 && s2[n])
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}
