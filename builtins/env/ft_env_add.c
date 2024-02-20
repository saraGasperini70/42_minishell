/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:50:43 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/20 14:56:21 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_env_add(const char *old_pwd, t_env *env)
{
	t_env	*tmp;
	t_env	*new;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(old_pwd);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->value = ft_strdup(old_pwd);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	env->next = tmp;
	return (SUCCESS);
}
