/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:21 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_quote(char *s, t_elem **ptr, enum e_token type, t_env *env)
{
	char	*value;

	*ptr = (*ptr)->next;
	while (*ptr && (*ptr)->type != type)
	{
		if (!s)
			s = ft_strdup("");
		if ((*ptr)->type == ENV && (*ptr)->state == IN_DQUOTE)
		{
			value = ft_get_env((*ptr)->content + 1, env);
			if (value)
				s = ft_strjoin(s, value);
		}
		else
			s = ft_strjoin(s, (*ptr)->content);
		*ptr = (*ptr)->next;
	}
	if (*ptr)
		*ptr = (*ptr)->next;
	return (s);
}

t_red_lst	*parse_redir(t_elem **ptr, t_red_lst *redir, t_env *env)
{
	enum e_token	type;
	char			*arg;

	type = (*ptr)->type;
	while ((*ptr)->type != W && (*ptr)->type != ENV)
		*ptr = (*ptr)->next;
	if ((*ptr)->type == ENV && type != HERE_DOC)
	{
		arg = ft_get_env((*ptr)->content + 1, env);
		if (!arg)
		{
			printf("bash: %s: ambiguous redirect\n", (*ptr)->content);
			return (NULL);
		}
	}
	else
		arg = ft_strdup((*ptr)->content);
	*ptr = (*ptr)->next;
	if (type == HERE_DOC)
		return (parse_here_doc(redir, arg, env->env));
	add_redir_tail(redir, new_redir_elem(arg, type));
	return (redir);
}

void	parse_word(t_elem **ptr, char **args, int *i)
{
	args[*i] = ft_strndup((*ptr)->content, (*ptr)->len);
	(*i)++;
	(*ptr) = (*ptr)->next;
}

t_ast_node	*parse_pipe(t_elem **ptr)
{
	t_ast_node	*node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	if (!node)
		return (NULL);
	node->type = PIPE;
	node->content = malloc(sizeof(t_union));
	node->content->pipe = malloc(sizeof(t_pipe));
	node->content->pipe->left = ft_calloc(sizeof(t_ast_node), 1);
	node->content->pipe->right = ft_calloc(sizeof(t_ast_node), 1);
	if (!node->content->pipe->right || !node->content->pipe->left)
		return (NULL);
	*ptr = (*ptr)->next;
	while ((*ptr)->type == ' ')
		*ptr = (*ptr)->next;
	return (node);
}

t_red_lst	*parse_here_doc(t_red_lst *redir, char *arg, char **env)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.minishell_tmp",
			O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, arg, ft_strlen(arg)) == 0)
			break ;
		else
		{
			if (ft_strchr(line, '$') != -1)
				line = exp_env(line, env);
			write(fd, line, ft_strlen(line));
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(arg);
	add_redir_tail(redir,
		new_redir_elem(ft_strdup("/tmp/.minishell_tmp"), HERE_DOC));
	close(fd);
	return (redir);
}
