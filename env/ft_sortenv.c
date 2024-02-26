/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:35:42 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/26 12:53:44 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_sortenv(char **tab, int env_len)
{
	int		sorted_check;
	int		i;
	char	*tmp;

	sorted_check = 0;
	while (tab && sorted_check == 0)
	{
		sorted_check = 1;
		i = 0;
		while (i < env_len -1)
		{
			if (ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + i];
				tab[i + 1] = tmp;
				sorted_check = 0;
			}
			i++;
		}
		env_len--;
	}
}
