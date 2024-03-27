/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:34:46 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_next_line(int fd)
{
	char	line[8000000];
	char	buf;
	char	*r;
	int		i;

	i = 0;
	write(1, "> ", 2);
	while (read(fd, &buf, 1) == 1)
	{
		line[i] = buf;
		if (buf == '\n')
		{
			break ;
		}
		i++;
	}
	line[i] = 0;
	i = 0;
	if (!line[i])
		return (NULL);
	r = ft_strdup(line);
	return (r);
}
