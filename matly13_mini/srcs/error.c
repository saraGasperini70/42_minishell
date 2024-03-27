/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:35:20 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_puterr(char *cmd, char *arg, char *msg, int err_num)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	if (!msg)
		perror("");
	else
		printf("%s\n", msg);
	g_data.exit_status = err_num;
	return (err_num);
}

int	p_err(t_elem *ptr)
{
	t_elem	*prev;
	t_elem	*next;
	int		result;

	prev = ign_space(ptr->prev, 0);
	next = ign_space(ptr->next, 1);
	result = prev->type != W && next->type != W;
	if ((!prev || !next) || (result && !is_redir(next->type)))
		return (1);
	return (0);
}

int	ft_perror(char *msg, char *utils)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (utils)
		write(STDERR_FILENO, utils, ft_strlen(utils));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

int	red_err(t_elem *ptr)
{
	t_elem	*next;

	next = ign_space(ptr->next, 1);
	if (!next || (next->type != W && next->type != ENV))
		return (1);
	return (0);
}
