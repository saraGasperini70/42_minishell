/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:34:38 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_separator(char c, char *stri)
{
	int	i;

	i = 0;
	while (stri[i])
	{
		if (c == stri[i])
		{
			return (1);
		}
		else
		{
			i++;
		}
	}
	return (0);
}

int	count_words(char *str, char *stri)
{
	int	i;
	int	w_count;
	int	state;

	i = -1;
	w_count = 0;
	state = 0;
	while (str[++i])
	{
		if (is_separator(str[i], stri))
		{
			state = 0;
		}
		else
		{
			if (!state)
			{
				w_count++;
			}
			state = 1;
		}
	}
	return (w_count);
}

char	*ft_strdup_split(char *str, int *index, char *stri)
{
	char	*word;
	int		len;
	int		i;

	i = *index;
	len = 0;
	while (str[i] && !is_separator(str[i], stri))
	{
		len++;
		i++;
	}
	word = (char *) malloc(len + 1);
	i = 0;
	while (str[*index])
	{
		if (is_separator(str[*index], stri))
			break ;
		else
		{
			word[i++] = str[*index];
			(*index)++;
		}
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char *str, char *stri)
{
	char	**arr_str;
	int		i;
	int		words;
	int		w_i;

	i = 0;
	w_i = 0;
	words = count_words(str, stri);
	arr_str = (char **) malloc((words + 1) * 8);
	if (!arr_str)
		return (NULL);
	while (w_i < words)
	{
		while (is_separator(str[i], stri) && str[i])
		{
			if (!str[i])
				break ;
			else
				i++;
		}
		arr_str[w_i] = ft_strdup_split(str, &i, stri);
		w_i++;
	}
	arr_str[words] = 0;
	return (arr_str);
}
