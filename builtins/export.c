#include "builtins.h"

static int	ft_print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("Export: not valid in this context: ", STDERR);
	if (error == 0 || error == -3)
		ft_putstr_fd("Export: not a valid identifier: ", STDERR);
	i = 0;
	while ((arg[i] && arg[i] != '=') || error == -3)
	{
		write (STDERR, &arg[i], 1);
		i++;
	}
	write (STDERR, "\n", 1);
	return (ERROR);
}

int	ft_env_add(const char *old_pwd, t_env *env)
{
	t_env	*tmp;
	t_env	*new;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(old_pwd);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->value = ft_strdup(old_pwd);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	env->next = tmp;
	return (SUCCESS);
}

char	*ft_get_envname(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isin_env(t_env *env, char *old_pwd)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	ft_get_envname(var_name, old_pwd);
	while (env && env->next)
	{
		ft_get_envname(env_name, env->value);
		if (ft_strncmp(var_name, env_name, ft_strlen(var_name)) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(old_pwd);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	new_env;
	int	error_ret;

	if (!args[1])
	{
		ft_print_sortedenv(secret);
		return (SUCCESS);
	}
	else
	{
		error_ret = ft_is_validenv(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (ft_print_error(error_ret, args[1]));
		if (error_ret == 2)
			new_env = 1;
		else
			new_env= ft_isin_env(env, args[1]);
		if (new_env == 0)
		{
			if (error_ret == 1)
				ft_env_add(args[1], env);
			ft_env_add(args[1], secret);
		}
	}
	return (SUCCESS);
}
