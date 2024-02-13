#include "builtins.h"

static void	ft_print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(":", 2);
	}
}

static char	*ft_get_envpath(t_env *env, const char *var, size_t len)
{
	char	*old_pwd;
	int		i;
	int		j;
	int		alloc_size;

	while (env && env->next != NULL)
	{
		alloc_size = ft_strlen(env->value) - len;
		old_pwd = malloc(sizeof(char) * alloc_size + 1);
		if (old_pwd == NULL)
			return (NULL);
		i = 0;
		j = 0;
		while (env->value[i++])
		{
			if (i > (int)len)
				old_pwd[j++] = env->value[i];
		}
		old_pwd[j] = '\0';
		return (old_pwd);
		env = env->next;
	}
	return (NULL);
}

static int	ft_update_oldpwd(t_env *env)
{
	char	cwd[_PC_PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, _PC_PATH_MAX) == NULL)
		return (ERROR);
	if (!ft_strjoin("OLDPWD=", cwd))
		return (ERROR);
	if (ft_isin_env(env, old_pwd) == 0)
		ft_env_add(old_pwd, env);
	ft_memdel(old_pwd);
	return (SUCCESS);
}

static int	ft_goto_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		ft_update_oldpwd(env);
		env_path = ft_get_envpath(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell: cd: HOME not found\n", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = ft_get_envpath(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell: cd: OLDPWD not found\n", STDERR);
		if (!env_path)
			return (ERROR);
	}
	ft_update_oldpwd(env);
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	ft_cd(char **str, t_env *env)
{
	int	cd_ret;

	if (!str)
		return (ft_goto_path(0, env));
	if (ft_strncmp(str[1], "-", ft_strlen(str[1])))
		cd_ret = ft_goto_path(1, env);
	else
	{
		env = ft_update_oldpwd(env);
		cd_ret = chdir(str[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			ft_print_error(str);
	}
	return (cd_ret);
}
