/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:13:18 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:46 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_mini_exit(t_mini *mini, char *cmd)
{
	mini->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	if (cmd[1] == 0)
		ft_putstr_fd("success ", STDERR);
	else
		ft_putstr_fd("Error ", STDERR);
	if (cmd[1] && cmd[2])
		ft_putstr_fd("Too many arguments ", STDERR);
	else if (ft_strisnum(&cmd[1]) == ERROR)
	{
		ft_putstr_fd("exit ", STDERR);
		ft_putstr_fd("numeric argument required ", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(&cmd[1]);
	else
		mini->ret = 0;
}
