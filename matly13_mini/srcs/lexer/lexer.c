/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:56 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_node(t_elem *node)
{
	int	i;

	i = 0;
	printf("content: ");
	while (i < node->len)
		printf("%c", node->content[i++]);
	printf(", len: %i", node->len);
	printf(", state: %i", node->state);
	printf(", token: %i\n", node->type);
}

t_list	*lex_checker(char *line)
{
	int				i;
	t_list			*tokens;
	enum e_state	state;

	i = 0;
	state = GENERAL;
	tokens = NULL;
	tokens = init_list(tokens);
	if (tokens)
	{
		while (line[i])
		{
			i = tokenize(tokens, line, i, &state);
		}
	}
	free(line);
	return (tokens);
}

int	tknz_redir(t_list *tokens, char *line, int i, enum e_state *state)
{
	int	j;

	j = i;
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			t_add(tokens, new_elem(line + (i++), 2, HERE_DOC, *state));
		else
			t_add(tokens, new_elem(line + (i), 1, RED_IN, *state));
		i++;
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			t_add(tokens, new_elem(line + (i++), 2, DRED_OUT, *state));
		else
			t_add(tokens, new_elem(line + (i), 1, RED_OUT, *state));
		i++;
	}
	return (i - j);
}

void	print_list(t_list *list)
{
	t_elem	*node;

	node = list->head;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
}

int	tokenize(t_list *tokens, char *line, int i, enum e_state *state)
{
	if (!in_charset(line[i]))
		i += get_word(tokens, line + i, *state);
	else if (line[i] == '\'')
		quotes_state(tokens, line + (i++), state, 1);
	else if (line[i] == '\"')
		quotes_state(tokens, line + (i++), state, 2);
	else if (line[i] == '$')
	{
		if (in_charset(line[i + 1]) || line[i + 1] == '=')
		{
			t_add(tokens, new_elem(line + i, 1, W, *state));
			i++;
		}
		else
			i += get_env_var(tokens, line + i, *state);
	}
	else if (line[i] == '>' || line[i] == '<')
		i += tknz_redir(tokens, line, i, state);
	else if (line[i] == '|')
		t_add(tokens, new_elem(line + (i++), 1, PIPE_LINE, *state));
	else if (ft_isspace(line[i]))
		t_add(tokens, new_elem(line + (i++), 1, ' ', *state));
	return (i);
}
