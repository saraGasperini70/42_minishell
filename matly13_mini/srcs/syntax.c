/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:36:55 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_elem	*ign_space(t_elem *ptr, int opt)
{
	while (ptr && ptr->type == ' ')
	{
		if (opt)
			ptr = ptr->next;
		else
			ptr = ptr->prev;
	}
	return (ptr);
}

char	*get_redir(enum e_token type)
{
	if (type == RED_IN)
		return ("<");
	if (type == RED_OUT)
		return (">");
	if (type == HERE_DOC)
		return ("<<");
	if (type == DRED_OUT)
		return (">>");
	return (".");
}

int	syn_err(t_list *list)
{
	t_elem	*ptr;

	ptr = list->head;
	while (ptr)
	{
		if (ptr->type == PIPE_LINE)
		{
			if (p_err(ptr))
				return (ft_perror("minishell: syntax error near"
						"unexpected token `|'", NULL));
		}
		else if (is_redir(ptr->type))
		{
			if (red_err(ptr))
				return (ft_perror("minishell: syntax error near"
						"unexpected token ", get_redir(ptr->type)));
		}
		else if (ptr->type == DOUBLE_QUOTE || ptr->type == QOUTE)
		{
			if (!uquo_check(&ptr, ptr->type))
				return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

t_elem	*uquo_check(t_elem **ptr, enum e_token type)
{
	const char	*t = "minishell: unclosed quotes detected.\n";

	while (*ptr)
	{
		*ptr = (*ptr)->next;
		if (!*ptr || (*ptr)->type == type)
			break ;
	}
	if (!*ptr)
		write(STDERR_FILENO, &t, ft_strlen((char *)t));
	return (*ptr);
}
