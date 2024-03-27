/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:26:55 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	join_for_echo(t_cmd **cmd, t_elem *ptr, char **env, int i)
{
	int	k;
	int	value;

	k = 0;
	value = check_cmd(ptr, env);
	while (++k < value && (*cmd)->args[i + k])
		(*cmd)->args[i] = ft_strjoin((*cmd)->args[i], (*cmd)->args[i + k]);
	return (value);
}

int	check_echo(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_opt(args[i]))
			return (i);
		i++;
		if (args[i] == NULL)
			return (i);
	}
	return (-1);
}

int	is_opt(char *opt)
{
	int	i;

	i = 1;
	if (opt[0] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_cmd(t_elem *ptr, char **env)
{
	int	value;

	value = 0;
	while (ptr && ptr->type != PIPE_LINE
		&& !is_redir(ptr->type) && ptr->type != ' ')
	{
		if (ptr->type == W || ptr->type == ENV)
			check_cmd_status(&ptr, env, &value);
		ptr = ptr->next;
	}
	return (value);
}

int	ft_echo(t_cmd *cmd, t_elem *lex, char **env)
{
	int		i;
	int		plus;
	t_bool	opt;

	opt = false;
	i = check_echo(cmd->args);
	if (i <= 1)
		i = 1;
	else
		opt = true;
	while (cmd->args[i])
	{
		plus = 0;
		plus = join_for_echo(&cmd,
				findek(lex, cmd->args[i], env), env, i);
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		ft_increaser(&i, plus);
		if (cmd->args[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!opt)
		write(STDOUT_FILENO, "\n", 1);
	g_data.exit_status = 0;
	return (0);
}
