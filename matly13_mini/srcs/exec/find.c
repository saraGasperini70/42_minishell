/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:30:12 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_sc(char *cmd, char **env)
{
	char	*cmd_path;

	if (cmd[0] == '/')
	{
		if (opendir(cmd) != NULL)
			printf("minishell: %s: is a directory\n", cmd);
		else if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			printf("minishell: %s: No such file or directory\n", cmd);
	}
	else if (cmd[0] == '.')
	{
		cmd_path = ft_join_dir(search_var("PWD", env), cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd);
		else
			printf("minishell: %s: No such file or directory\n", cmd);
	}
	return (NULL);
}

char	*findp(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	i = 0;
	path = search_var("PATH", env);
	paths = ft_split(path, ":");
	cmd_path = ft_strdup("");
	if (!cmd_path)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_join_dir(paths[i], cmd);
		if (cmd_path)
		{
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			i++;
			free(cmd_path);
		}
	}
	printf("minishell: %s: command not found\n", cmd);
	return (NULL);
}

char	*findc(char *cmd, char **env)
{
	char	*cmd_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		cmd_path = find_sc(cmd, env);
	else
		cmd_path = findp(cmd, env);
	if (cmd_path)
		return (cmd_path);
	exit(1);
	return (NULL);
}

int	*findrl(t_ast_node *ptr)
{
	return (&ptr->content->pipe->right->content-> \
		pipe->left->content->cmd->fd.out);
}
