/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:27:53 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd, char **env)
{
	(void) env;
	flx(g_data.lex);
	rem_env(g_data.ev);
	if (g_data.alloc)
		f2d(env);
	printf("exit\n");
	if (check_args(cmd->args))
		return (1);
	g_data.exit_status = ft_atoi(cmd->args[1]);
	fp(g_data.t);
	exit(g_data.exit_status);
	return (0);
}

int	check_args(char **args)
{
	if (args[0] && !args[1])
	{
		fp(g_data.t);
		exit(0);
	}
	if (number_of_args(args) > 2)
	{
		fp(g_data.t);
		printf("minishel: exit: too many arguments\n");
		g_data.exit_status = 1;
		return (1);
	}
	if (!ft_isnum(args[1]))
	{
		fp(g_data.t);
		printf("exit: %s: numeric argument required\n", args[1]);
		g_data.exit_status = 255;
		exit(255);
	}
	return (0);
}

int	number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
