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

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

# define ERROR 1
# define SUCCESS 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

int	ft_echo(char **args);
int	ft_cd(char **str, t_env *env);

int	ft_isin_env(t_env *env, char **old_pwd);
int	ft_env_add(char *old_pwd, t_env *env);

#endif
