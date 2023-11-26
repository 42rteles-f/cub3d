/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:41:19 by rteles-f          #+#    #+#             */
/*   Updated: 2023/10/23 17:41:19 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	remove_from_list(void *find, t_list **head)
{
	t_list	*node;
	t_list	*previous;

	previous = NULL;
	node = *head;
	while (node)
	{
		if (node->content == find)
		{
			if (previous)
				previous->next = node->next;
			else
				*head = node->next;
			free(node);
			return ;
		}
		previous = node;
		node = node->next;
	}
}

static void	new_list_member(void *content)
{
	t_list	*list;
	t_list	*last;

	if (!content)
		return ;
	list = **(void ***)this();
	last = NULL;
	while (list)
	{
		if (list->content == content)
			return ;
		last = list;
		list = list->next;
	}
	if (!*this())
		*this() = ft_lstnew(content);
	else
		ft_lstadd_back(*this(), ft_lstnew(content));
}

static void	destroy(void)
{
	t_list	*node;
	t_list	*hold;

	node = **(void ***)this();
	while (node)
	{
		((t_object *)node->content)->destroy(node->content);
		hold = node->next; 
		free(node);
		node = hold;
	}
	**(void ***)this() = NULL;
}

static void	run_list(void (*apply)(), void *arg1, void *arg2)
{
	t_list	*list;

	list = **(void ***)this();
	while (list)
	{
		apply(list->content, arg1, arg2);
		list = list->next;
	}
}

inline t_lister	*list(void *list)
{
	static t_lister	manager = {
		new_list_member,
		run_list,
		destroy
	};

	*this() = list;
	return (&manager);
}
