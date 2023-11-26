/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:53:44 by lliberal          #+#    #+#             */
/*   Updated: 2023/11/10 21:02:06 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strchr(const char *string, int c)
{
	int	i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (unsigned char)c)
			return (&((char *)string)[i]);
		i++;
	}
	if (string[i] == (unsigned char)c)
		return (&((char *)string)[i]);
	return (NULL);
}

int	ft_strlen(const char *string)
{
	int	counter;

	if (!string)
		return (0);
	counter = 0;
	while (string[counter])
		counter++;
	return (counter);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0'
		&& s1[i] == s2[i] && i < (n - 1))
		i++;
	return ((((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
}

char	*ft_strrchr(const char *string, int c)
{
	int		len;

	len = ft_strlen(string);
	while (len > -1)
	{
		if (string[len] == (char)c)
			return ((char *)&string[len]);
		len--;
	}
	return (NULL);
}

char	*cut_str(char *str)
{
	int	index[2];

	if (!str)
		return (NULL);
	index[0] = 0;
	while (ft_isspace(str[index[0]]))
		index[0]++;
	index[1] = 0;
	while (str[index[1]])
		index[1]++;
	while (ft_isspace(str[--index[1]]))
		;
	return (substr_no_memory(str, index[0], index[1]));
}
