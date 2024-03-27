/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:26:48 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_dir(t_env *ev, char *cwd, char *owd)
{
	t_env_el	*env_elem;

	env_elem = search_el(ev, "PWD");
	if (!env_elem)
	{
		return ;
	}
	env_elem->value = ft_strdup(cwd);
	env_elem = search_el(ev, "OLDPWD");
	if (!env_elem)
	{
		return ;
	}
	env_elem->value = ft_strdup(owd);
}

int	ft_cd(t_cmd *cmd, char ***env)
{
	t_env	*ev;
	char	cwd[1024];
	char	owd[1024];

	ev = new_env(*env);
	getcwd(owd, sizeof(owd));
	if (!cmd->args[1])
	{
		if (chdir(exp_env("$HOME", *env)) != 0)
			return (ft_puterr(cmd->args[0], exp_env("$HOME", *env), NULL, 1));
	}
	else
	{
		if (chdir(cmd->args[1]) != 0)
		{
			return (ft_puterr(cmd->args[0], cmd->args[1], NULL, 1));
		}
	}
	getcwd(cwd, sizeof(cwd));
	set_dir(ev, cwd, owd);
	*env = arr_conv(ev);
	g_data.exit_status = 0;
	return (0);
}
