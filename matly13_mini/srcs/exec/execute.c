/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:30:02 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_ccmd(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "export") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "unset") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "pwd") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "exit") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "cd") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "env") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "echo") == EQUAL))
		return (1);
	return (0);
}

void	ft_hub_cmd(t_cmd *cmd, char ***env, t_elem *head)
{
	if (cmd->args[0] && (ft_strcmp(cmd->args[0], "export") == EQUAL))
		ft_export(env, cmd, head);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "unset") == EQUAL))
		ft_unset(cmd, env);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "pwd") == EQUAL))
		ft_pwd(cmd);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "exit") == EQUAL))
		ft_exit(cmd, *env);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "cd") == EQUAL))
		ft_cd(cmd, env);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "env") == EQUAL))
		ft_env(cmd, *env);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "echo") == EQUAL))
		ft_echo(cmd, head, *env);
}

void	check_pid(int pid, int count, int count_cmd)
{
	int	status;

	status = 0;
	if (count == count_cmd)
	{
		waitpid(pid, &status, 0);
		if (!g_data.which)
			g_data.exit_status = WEXITSTATUS(status);
	}
}

int	exec_builtin(t_ast_node *ptr, char ***env, t_elem *head, int fd[2])
{
	int	pid;

	pid = 0;
	if (check_ccmd(ptr->content->cmd->args[0]) == 1)
		exec_built(ptr->content->cmd, env, head);
	else
		pid = exec_cmd(ptr->content->cmd, *env, fd);
	return (pid);
}

void	exec_all(t_ast_node *ptr, char ***env, int count_cmd, t_elem *head)
{
	int			fd[2];
	int			pid;
	static int	count;

	pid = 0;
	if (ptr->type == CMD)
	{
		pid = exec_builtin(ptr, env, head, fd);
		count++;
	}
	else if (ptr->type == PIPE)
	{
		if (pipe(fd) < 0)
			return ;
		if (ptr->content->pipe->right->type == CMD)
			dup_fds(&ptr->content->pipe->right->content->cmd->fd.out, fd[1]);
		else if (ptr->content->pipe->right->type == PIPE)
			dup_fds(findrl(ptr), fd[1]);
		dup_fds(&ptr->content->pipe->left->content->cmd->fd.in, fd[0]);
		exec_all(ptr->content->pipe->right, env, count_cmd, head);
		exec_all(ptr->content->pipe->left, env, count_cmd, head);
		close(fd[0]);
		close(fd[1]);
	}
	check_pid(pid, count, count_cmd);
}
