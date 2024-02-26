/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_validenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:34:19 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/26 12:53:31 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_is_validenv(char *args)
{
	int	i;

	i = 0;
	if (ft_isdigit(args[i]))
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]))
			return (-1);
		i++;
	}
	if (args[i] != '=')
		return (2);
	return (1);
}
