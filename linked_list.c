/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:27:40 by cbessonn          #+#    #+#             */
/*   Updated: 2023/09/22 12:56:53 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*li;

	if (*lst == 0)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	li = *lst;
	while (li->next)
		li = (li)->next;
	(li)->next = new;
	li = li->next;
	li->next = NULL;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (0);
	element->content = content;
	element->next = NULL;
	return (element);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		free((*lst)->content);
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
}
