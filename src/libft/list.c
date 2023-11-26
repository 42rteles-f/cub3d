/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:00:12 by lliberal          #+#    #+#             */
/*   Updated: 2023/10/10 16:31:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iterate;

	iterate = *lst;
	if (!lst || !new)
		return ;
	if (iterate)
	{
		while (iterate->next)
			iterate = iterate->next;
		iterate->next = new;
	}
	else
		*lst = new;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delete;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		delete = (*lst);
		(*lst) = (*lst)->next;
		(*del)(delete->content);
		free(delete);
		delete = NULL;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}
