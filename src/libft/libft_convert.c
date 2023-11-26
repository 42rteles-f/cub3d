/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:23:09 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 18:18:38 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	number;

	if (!nptr)
		return (0);
	i = 0;
	while ((8 < nptr[i] && nptr[i] < 14) || nptr[i] == 32)
		i++;
	sign = (nptr[i] != '-') - (nptr[i] == '-');
	i += (nptr[i] == '-' || nptr[i] == '+');
	number = 0;
	while (47 < nptr[i] && nptr[i] < 58)
		number = (nptr[i++] - 48) + (number * 10);
	return ((int)(number * sign));
}

char	*ft_itoa(int number)
{
	char	to_ascii[12];
	char	*string;
	int		index;
	int		sign;

	sign = (number > 0) - (number < 0);
	index = 11;
	while (number || index == 11)
	{
		to_ascii[--index] = (number % 10) * sign + '0';
		number = number / 10;
	}
	if (sign < 0)
		to_ascii[--index] = '-';
	string = ft_calloc(sizeof(char), (12 - index));
	if (!string)
		return (NULL);
	sign = 0;
	while (index < 11)
		string[sign++] = to_ascii[index++];
	return (string);
}

char	**ft_aux(char	**str, char const *s, char c, int count)
{
	int		size;
	int		i;
	char	*line;

	size = 0;
	i = 0;
	line = NULL;
	while (*s && *s == c)
		s++;
	while (s[size] && s[size] != c)
		size++;
	if (size)
		line = ft_calloc((size + 1), sizeof(char));
	while (line && *s && *s != c)
		line[i++] = *s++;
	if (line)
		str = ft_aux(str, s, c, count + 1);
	else
		str = ft_calloc((count + 1), sizeof(char *));
	if (str)
		str[count] = line;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	return (ft_aux(NULL, s, c, 0));
}
