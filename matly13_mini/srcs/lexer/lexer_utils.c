/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:44 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c <= 32)
	{
		return (1);
	}
	return (0);
}

int	get_env_var(t_list *tokens, char *str, enum e_state state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while (is_alphanum(str[i]) && str[i] != '\n' && str[i] != '\0')
			i++;
	t_add(tokens, new_elem(str, i, ENV, state));
	return (i);
}

int	in_charset(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || ft_isspace(c) || c == '\n' || c == '\0');
}

int	get_word(t_list *tokens, char *str, enum e_state state)
{
	int	i;

	i = 0;
	while (!in_charset(str[i]))
		i++;
	t_add(tokens, new_elem(str, i, W, state));
	return (i);
}

void	quotes_state(t_list *t, char *str, enum e_state *state, int flag)
{
	enum e_state	e_state;
	enum e_token	e_type;

	e_state = IN_DQUOTE;
	e_type = DOUBLE_QUOTE;
	if (flag == 1)
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
	if (*state == GENERAL)
	{
		t_add(t, new_elem(str, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{
		*state = GENERAL;
		t_add(t, new_elem(str, 1, e_type, *state));
	}
	else
		t_add(t, new_elem(str, 1, e_type, *state));
}
