/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:32:42 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*init_tree(t_ast *tree)
{
	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->root = NULL;
	return (tree);
}

void	print_tree(t_ast_node *ptr, char **env)
{
	if (ptr->type == CMD)
	{
		printf("\n------------------------\n");
		printf("CMD Node\n");
		print_ast_node(ptr);
	}
	else if (ptr->type == PIPE)
	{
		print_tree(ptr->content->pipe->right, env);
		printf("\n------------------------\n");
		printf("PIPE Node\n");
		print_tree(ptr->content->pipe->left, env);
	}
}

t_ast_node	*create_cmd(char **args, char **env, t_red_lst *redir)
{
	t_ast_node	*n;

	n = malloc(sizeof(t_ast_node));
	n->content = malloc(sizeof(t_union));
	n->content->cmd = malloc(sizeof(t_cmd));
	if (!n || !n->content || !n->content->cmd)
	{
		return (NULL);
	}
	n->type = CMD;
	n->content->cmd->args = args;
	n->content->cmd->env = env;
	n->content->cmd->redir = redir;
	n->content->cmd->fd.in = 0;
	n->content->cmd->fd.out = 1;
	return (n);
}

void	ftree(t_ast_node *n)
{
	if (n->type == CMD)
	{
		fcmd(n->content->cmd);
		free(n->content);
		free(n);
	}
	else if (n->type == PIPE)
	{
		ftree(n->content->pipe->right);
		ftree(n->content->pipe->left);
		free(n->content->pipe);
		free(n->content);
		free(n);
	}
}

void	print_ast_node(t_ast_node *cmd)
{
	int	i;

	i = 0;
	while (cmd->content->cmd->args[i])
	{
		printf("command arg[%i]: %s\n", i, cmd->content->cmd->args[i]);
		i++;
	}
	print_red_lst(cmd->content->cmd->redir);
	printf("fd->in: %d, fd->out: %d\n", cmd->content->cmd->fd.in,
		cmd->content->cmd->fd.out);
}
