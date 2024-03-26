#include "../includes/builtins.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == 0)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": no such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": permission denied", STDERR);
	if ((ft_strchr(path, '/') == NULL || fd == -1) && folder == NULL)
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strncmp(item->d_name, command, ft_strlen(item->d_name)) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int	exec_process2(int sigin, t_sig pid)
{
	int	ret;

	ret = 0;
	if (sigin == 1 || pid.pid == 1)
	{
		if (ret == 32256)
			ret = (ret / 256);
		else if (ret == 32512)
			ret = !!ret;
	}
	return (ret);
}

int	ft_exec_process(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	char	*ptr;
	int		ret;
	t_sig	pid;

	ret = SUCCESS;
	pid.pid = fork();
	if (pid.pid == 0)
	{
		ptr = ft_env_tostr(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		ft_free_alloc(env_array);
		ft_free_token(mini->start);
		exit(ret);
	}
	else
		waitpid(pid.pid, &ret, 0);
	ret = exec_process2(pid.sigin, pid);
	return (ret);
}

int	ft_exec_bin(char **args, t_env *env, t_mini *mini)
{
	int		i;
	int		result;
	char	**bin;
	char	*path;

	i = 0;
	result = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env != NULL || env->next == NULL)
		return (ft_exec_process(args[0], args, env, mini));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		result = ft_exec_process(path, args, env, mini);
	else
		result = ft_exec_process(args[0], args, env, mini);
	ft_free_alloc(bin);
	ft_memdel(path);
	return (result);
}
