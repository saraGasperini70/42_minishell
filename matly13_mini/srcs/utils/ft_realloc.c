/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:34:31 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst)
		return (0);
	if (!src)
		return (0);
	i = -1;
	while (++i < n)
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
	return (dst);
}

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new;

	new = malloc(sizeof(void) * new_size);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
