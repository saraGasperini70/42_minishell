/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:15:51 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/20 13:19:07 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(t_env *env)
{
	char cwd[_PC_PATH_MAX];

	if (getcwd(cwd, _PC_PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
