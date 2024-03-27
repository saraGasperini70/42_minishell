/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:27:45 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		g_data.exit_status = 1;
		return (ft_perror("minishell: env: Too many arguments.", NULL));
	}
	else
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '=') != -1)
			{
				printf("%s\n", env[i]);
			}
			i++;
		}
	}
	return (0);
}
