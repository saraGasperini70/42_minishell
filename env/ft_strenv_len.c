/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strenv_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:50 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/28 12:02:20 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_strenv_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
