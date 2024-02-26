/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sortedenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:34:23 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/26 12:53:41 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	ft_print_sortedenv(t_env *env)
{
	char	**env_matrix;
	char	*env_str;
	int		i;

	env_str = ft_env_tostr(env);
	env_matrix = ft_split(env_str, '\n');
	ft_memdel(env_str);
	ft_sortenv(env_matrix, ft_strenv_len(env_matrix));
	i = 0;
	while (env_matrix[i])
	{
		ft_putstr_fd("Declare -x ", STDOUT);
		ft_putendl_fd(env_matrix[i], STDOUT);
		i++;
	}
	ft_free_alloc(env_matrix);
}
