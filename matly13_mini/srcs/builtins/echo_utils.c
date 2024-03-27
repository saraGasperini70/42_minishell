/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:26:20 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_increaser(int *i, int plus)
{
	if (plus)
		(*i) += plus;
	else
		(*i)++;
}

void	check_cmd_status(t_elem**ptr, char **env, int *value)
{
	if ((*ptr)->state != GENERAL)
	{
		while ((*ptr) && (*ptr)->state != GENERAL)
		{
			(*ptr) = (*ptr)->next;
		}
		(*value)++;
	}
	else
	{
		(*value)++;
		if ((*ptr)->type == ENV)
		{
			if (ft_strcmp(exp_env((*ptr)->content, env), "") == EQUAL)
				(*value)--;
		}
	}
}
