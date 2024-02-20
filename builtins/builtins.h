/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:33:58 by sgasperi          #+#    #+#             */
/*   Updated: 2024/02/20 12:48:02 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

# define ERROR 1
# define SUCCESS 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFF_SIZE 4096

int		ft_echo(char **args);
char	*ft_alloc_str(int alloc_size);
int		ft_cd(char **str, t_env *env);

int		ft_export(char **args, t_env *env, t_env *secret);

int		ft_isin_env(t_env *env, char *old_pwd);
int		ft_env_add(const char *old_pwd, t_env *env);
char	*ft_get_envname(char *dest, char *src);
int		ft_print_sortedenv(t_env *secret);
int		ft_is_validenv(char *args);

#endif
