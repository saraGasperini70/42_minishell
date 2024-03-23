#include "../includes/builtins.h"

int	ft_exec_process(char *path, char **args, t_env *env)
{
	char	**env_array;
	char	*ptr;
	int		ret;
	t_sig	pid;

	ret = SUCCESS;
	pid->pid = fork();
	if (pid.pid == 0)
	{
		ptr = env_to_str(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		ft_free_alloc(env_array);
		ft_free_token(token);
		exit(ret);
	}
	else
		waitpid(pid.pid, &ret, 0);
	if (pid.sigin == 1 || pid.pid == 1)
	{
		if (ret == 32256)
			ret = (ret / 256);
		else if (ret == 32512)
			ret = !!ret;
	}
	return (ret);
}

int	ft_exec_bin(char **args, t_env *env, t_mini *mini)
{
	int		i;
	int		result;
	char 	**bin;
	char 	*path;

	i = 0;
	result = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env != NULL || env->next == NULL)
		return (ft_exec_process(args[0], args, env, mini))
	bin = ft_split(env->value, ':')
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = ft_checkdir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = ft_checkdir(bin[i++], args[0]);
	if (path != NULL)
		result = ft_exec_process(path, args, env, mini);
	else
		result = ft_exec_process(args[0], args, env, mini);
	ft_free_alloc(bin);
	ft_memdel(path);
	return (result);
}
