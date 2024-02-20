/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:47:17 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/20 12:47:44 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isin_env(t_env *env, char *old_pwd)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	ft_get_envname(var_name, old_pwd);
	while (env && env->next)
	{
		ft_get_envname(env_name, env->value);
		if (ft_strncmp(var_name, env_name, ft_strlen(var_name)) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(old_pwd);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}
