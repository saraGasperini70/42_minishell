/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:14 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_redir_out(t_red_lst *list, t_fd *fd)
{
	t_red_el	*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (tmp->type == RED_IN)
			exec_redir_in(tmp, &fd->in);
		else if (tmp->type == RED_OUT)
		{
			close(fd->out);
			(fd)->out = open(tmp->arg, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		else if (tmp->type == DRED_OUT)
		{
			close(fd->out);
			(fd)->out = open(tmp->arg, O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		else if (tmp->type == HERE_DOC)
		{
			close(fd->in);
			fd->in = open(tmp->arg, O_RDONLY, 0666);
		}
		tmp = tmp->next;
	}
}

void	exec_redir_in(t_red_el *tmp, int *in)
{
	if (access(tmp->arg, F_OK) != 0)
	{
		*in = -1;
		write(2, "minishell: ", 11);
		ft_perror(tmp->arg, ": No such file or directory");
	}
	else
	{
		close(*in);
		*in = open(tmp->arg, O_RDONLY, 0666);
	}
}
