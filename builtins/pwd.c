/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:15:51 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/26 12:56:37 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_pwd(void)
{
	char	cwd[_PC_PATH_MAX];

	if (getcwd(cwd, _PC_PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
