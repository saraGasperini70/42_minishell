/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:41 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_red_lst	*init_red_lst(t_red_lst *list)
{
	list = ft_calloc(sizeof(t_red_lst), 1);
	if (!list)
		return (NULL);
	return (list);
}

void	frlst(t_red_lst *list)
{
	t_red_el	*tmp;

	tmp = list->head;
	while (tmp)
	{
		free(tmp->arg);
		free(tmp);
		tmp = tmp->next;
	}
	free(list);
}

void	add_redir_tail(t_red_lst *list, t_red_el *new)
{
	if (!list->head)
	{
		list->head = new;
	}
	else
	{
		list->tail->next = new;
	}
	list->tail = new;
	list->size++;
}

void	print_red_lst(t_red_lst *redir)
{
	t_red_el	*tmp;

	tmp = redir->head;
	if (tmp)
	{
		printf("REDIR LIST\n");
	}
	while (tmp)
	{
		printf("redir type: %i\n", tmp->type);
		printf("redir arg: %s\n", tmp->arg);
		tmp = tmp->next;
	}
}

t_red_el	*new_redir_elem(char *arg, enum e_token type)
{
	t_red_el	*elem;

	elem = ft_calloc(sizeof(t_red_el), 1);
	if (!elem)
	{
		return (NULL);
	}
	elem->arg = arg;
	elem->type = type;
	return (elem);
}
