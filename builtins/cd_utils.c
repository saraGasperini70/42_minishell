/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:44:16 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/28 12:29:42 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	*ft_alloc_str(int alloc_size)
{
	char	*old_pwd;

	old_pwd = malloc(sizeof(char) * alloc_size + 1);
	if (!(old_pwd))
		return (NULL);
	return (old_pwd);
}

void	ft_free_alloc(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix[i]);
	free(matrix);
}

void	ft_free_node(t_mini *mini, t_env *env)
{
	if (mini->env && mini->env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
