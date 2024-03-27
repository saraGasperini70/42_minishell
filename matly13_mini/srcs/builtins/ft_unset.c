/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:29:42 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_unset(t_cmd *cmd, char ***ev)
{
	t_env	*env;
	int		i;

	i = 1;
	env = NULL;
	env = new_env(*ev);
	g_data.exit_status = 0;
	while (cmd->args[i])
	{
		unset_env(cmd->args[i], env);
		i++;
	}
	*ev = arr_conv(env);
	rem_env(env);
	return (g_data.exit_status);
}

void	unset_env(char *args, t_env *env)
{
	t_env_el	*elem;

	elem = NULL;
	if (args && !ft_isalpha(args[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			args);
		g_data.exit_status = 1;
	}
	else
	{
		elem = search_el(env, args);
		if (elem)
			rem_env_elem(env, elem);
	}
}
