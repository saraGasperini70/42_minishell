/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:29:34 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	cwd[1024];
	char	*dir;

	dir = getcwd(cwd, sizeof(cwd));
	(void)cmd;
	if (!dir)
	{
		g_data.exit_status = 1;
		perror("minishell: pwd: ");
		return (-1);
	}
	else
	{
		g_data.exit_status = 0;
		printf("%s\n", dir);
		return (0);
	}
}
