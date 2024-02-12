#include "builtins.h"
static int	ft_goto_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;
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
