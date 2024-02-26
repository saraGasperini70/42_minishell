/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:34:10 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/26 12:53:17 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	ft_print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("Export: not valid in this context: ", STDERR);
	if (error == 0 || error == -3)
		ft_putstr_fd("Export: not a valid identifier: ", STDERR);
	i = 0;
	while ((arg[i] && arg[i] != '=') || error == -3)
	{
		write (STDERR, &arg[i], 1);
		i++;
	}
	write (STDERR, "\n", 1);
	return (ERROR);
}

static int	ft_arg_check(char *arg, t_env *env, int error_ret)
{
	int	new_env;

	if (error_ret <= 0)
		return (ft_print_error(error_ret, arg));
	if (error_ret == 2)
		new_env = 1;
	else
		new_env = ft_isin_env(env, arg);
	return (new_env);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	new_env;
	int	error_ret;

	if (!args[1])
	{
		ft_print_sortedenv(secret);
		return (SUCCESS);
	}
	else
	{
		error_ret = ft_is_validenv(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		new_env = ft_arg_check(args[1], env, error_ret);
		if (new_env == 0)
		{
			if (error_ret == 1)
				ft_env_add(args[1], env);
			ft_env_add(args[1], secret);
		}
	}
	return (SUCCESS);
}
