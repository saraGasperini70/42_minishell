/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:44:16 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/20 12:44:42 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
