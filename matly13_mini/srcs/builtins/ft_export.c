/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:29:20 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_i(t_env *env, char *args_i, char **tmp, int index)
{
	t_env_el	*env_elem;

	env_elem = NULL;
	if (index != -1)
	{
		tmp = split_env(args_i);
		env_elem = search_el(env, tmp[0]);
		if (env_elem)
		{
			free(env_elem->value);
			env_elem->value = ft_strdup(tmp[1]);
		}
		else
			add_env_elem(env, new_env_elem(args_i));
		f2d(tmp);
	}
	else
	{
		env_elem = search_el(env, args_i);
		if (!env_elem)
			add_env_elem(env, new_env_elem(args_i));
	}
}

int	join_args(t_cmd **cmd, t_elem *ptr, char **env, int i)
{
	int	k;
	int	value;

	k = 0;
	value = check_export(ptr, env);
	while (++k < value && (*cmd)->args[i + k])
		(*cmd)->args[i] = ft_strjoin((*cmd)->args[i], (*cmd)->args[i + k]);
	f2d(env);
	return (value);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_export(char ***ev, t_cmd *cmd, t_elem *head)
{
	t_env	*env;

	env = NULL;
	env = new_env(*ev);
	if (!cmd->args[1])
		print_sorted_env(env);
	else
	{
		if (!ft_isalpha(cmd->args[1][0]))
			return (ft_puterr(cmd->args[0],
					cmd->args[1], "not a valid identifier", 1));
		handle_env(env, cmd, head);
		g_data.env = arr_conv(env);
		*ev = arr_conv(env);
		g_data.alloc = 1;
	}
	rem_env(env);
	g_data.exit_status = 0;
	return (0);
}

void	handle_env(t_env *env, t_cmd *cmd, t_elem *head)
{
	char		**tmp;
	int			i;
	int			plus;
	int			index;

	i = 1;
	tmp = NULL;
	while (cmd->args[i])
	{
		plus = 0;
		plus += join_args(&cmd, findek(head, cmd->args[i],
					arr_conv(env)), arr_conv(env), i);
		index = ft_strchr(cmd->args[i], '=');
		check_i(env, cmd->args[i], tmp, index);
		if (!plus)
			i++;
		else
			i += plus;
	}
}
