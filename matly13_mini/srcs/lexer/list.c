/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:32:35 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*init_list(t_list *list)
{
	list = ft_calloc(sizeof(t_list), 1);
	if (!list)
	{
		return (NULL);
	}
	return (list);
}

void	fl(t_list *list)
{
	t_elem	*tmp;

	tmp = list->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}

t_elem	*new_elem(char *str, int l, enum e_token type, enum e_state state)
{
	t_elem	*elem;
	char	*cont;

	elem = ft_calloc(sizeof(t_elem), 1);
	if (!elem)
		return (NULL);
	cont = ft_strndup(str, l);
	if (!cont)
		return (NULL);
	elem->content = cont;
	elem->len = l;
	elem->type = type;
	elem->state = state;
	return (elem);
}

void	t_add(t_list *list, t_elem *new)
{
	if (!is_empty(list))
	{
		list->tail->next = new;
		new->prev = list->tail;
	}
	else
		list->head = new;
	list->tail = new;
	list->size++;
}

int	is_empty(t_list *list)
{
	if (list->head == NULL)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
