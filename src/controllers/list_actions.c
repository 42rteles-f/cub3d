/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:14:34 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:14:34 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	delete_node(void *delete)
{
	t_list	*node;

	node = **(void ***)this();
	while (node)
	{
		if (node->content == delete)
		{
			node->previous->next = node->next;
			((t_object *)node->content)->destroy(node->content);
			free(node);
			return ;
		}
		node = node->next;
	}
}

t_list	*find_node(int find)
{
	t_list	*node;

	node = **(void ***)this();
	while (node)
	{
		if (((t_object *)node->content)->id == find)
			return (node->content);
	}
	return (NULL);
}
