/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:59:34 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 18:20:55 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*substr_no_memory(char *str, int start, int end)
{
	int	i;

	if (!str || start > end)
		return (NULL);
	i = 0;
	while (str[start] && start <= end)
		str[i++] = str[start++];
	while (str[i])
		str[i++] = 0;
	return (str);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	if (!s)
		return (NULL);
	copy = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	return (copy);
}

void	*trim_no_memory(char *str, char *set)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = 0;
	while (ft_strchr(set, str[i]))
		i++;
	j = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		str[j++] = str[i++];
	while (str[j])
		str[j++] = 0;
	return (NULL);
}

void	*ft_calloc(size_t n, size_t xsize)
{
	char	*new;
	size_t	i;
	size_t	total;

	total = (n * xsize);
	new = malloc(total);
	if (!new)
		return (NULL);
	i = 0;
	while (i < total)
		new[i++] = 0;
	return (new);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
