/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:00 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_action(t_elem **ptr, t_env *env, char **args, int *i)
{
	args[*i] = ft_get_env((*ptr)->content + 1, env);
	if (args[*i])
		(*i)++;
	(*ptr) = (*ptr)->next;
}

t_ast_node	*parse_cmd(t_elem **ptr, t_env *env)
{
	t_ast_node		*new;
	char			**args;
	t_red_lst		*redir;
	int				size;

	redir = NULL;
	size = count_argouments((*ptr));
	args = ft_calloc(sizeof(char *), (size + 1));
	redir = init_red_lst(redir);
	if (!args || !redir)
	{
		return (NULL);
	}
	if (pcmd_act(ptr, env, redir, args) == 1)
	{
		return (NULL);
	}
	new = create_cmd(args, env->env, redir);
	return (new);
}

t_red_lst	*redir_act(t_elem **ptr, t_env *env, t_red_lst *redir)
{
	return (parse_redir(ptr, redir, env));
}

int	parse(t_ast **tree, t_elem *ptr, t_env *env)
{
	t_ast_node	*tmp_node;

	tmp_node = NULL;
	if (!ptr)
		return (1);
	tmp_node = parse_cmd(&ptr, env);
	if (!tmp_node)
		return (1);
	if (!(*tree)->root)
		(*tree)->root = tmp_node;
	else
	{
		if (!(*tree)->root->content->pipe->right)
			(*tree)->root->content->pipe->right = tmp_node;
		else
			(*tree)->root->content->pipe->left = tmp_node;
	}
	if (ptr && ptr->type == PIPE_LINE)
	{
		tmp_node = parse_pipe(&ptr);
		tmp_node->content->pipe->right = (*tree)->root;
		(*tree)->root = tmp_node;
	}
	parse(tree, ptr, env);
	return (0);
}

int	pcmd_act(t_elem **ptr, t_env *env, t_red_lst *redir, char **args)
{
	int	i;

	i = 0;
	while ((*ptr) && (*ptr)->type != PIPE_LINE)
	{
		if ((*ptr)->type == W)
			parse_word(ptr, args, &i);
		else if ((*ptr)->type == ' ')
			(*ptr) = (*ptr)->next;
		else if ((*ptr)->type == DOUBLE_QUOTE || (*ptr)->type == QOUTE)
		{
			args[i] = parse_quote(args[i], ptr, (*ptr)->type, env);
			if (args[i])
				(i)++;
		}
		else if ((*ptr)->type == ENV)
			env_action(ptr, env, args, &i);
		else if (is_redir((*ptr)->type))
		{
			if (!redir_act(ptr, env, redir))
				return (1);
		}
	}
	args[i] = NULL;
	return (0);
}
