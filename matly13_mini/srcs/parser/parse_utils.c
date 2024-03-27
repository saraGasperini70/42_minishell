/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:12 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir(enum e_token type)
{
	return (type == RED_IN || type == RED_OUT || type == DRED_OUT || \
		type == HERE_DOC);
}

int	count_argouments(t_elem *elem)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp && tmp->type != PIPE_LINE)
	{
		if (tmp->type == W || tmp->type == ENV)
		{
			i++;
		}
		else if (tmp->type == DOUBLE_QUOTE || tmp->type == QOUTE
			|| is_redir(tmp->type))
			count_redir_args(&tmp, tmp->type, &i);
		if (tmp)
		{
			tmp = tmp->next;
		}
	}
	return (i);
}

void	count_redir_args(t_elem **elem, enum e_token type, int *i)
{
	if (type == DOUBLE_QUOTE || type == QOUTE)
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type != type)
		{
			(*elem) = (*elem)->next;
		}
		(*i)++;
	}
	else if (is_redir(type))
	{
		while ((*elem)->type != W && (*elem)->type != ENV)
		{
			(*elem) = (*elem)->next;
		}
		(*elem) = (*elem)->next;
	}
}
