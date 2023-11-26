/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:14:46 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/10 21:15:33 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

inline t_engine	*engine(void)
{
	static t_engine	engine;

	return (&engine);
}

inline void	**this(void)
{
	static void	*obj;

	return (&obj);
}

t_list	**offstage(void)
{
	static t_list	*list;

	return (&list);
}

t_list	**onstage(void)
{
	static t_list	*list;

	return (&list);
}
