#include "../includes/builtins.h"

int	ft_is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)))
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)))
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)))
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)))
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)))
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)))
		return (1);
	return (0);
}

int	ft_exec_builtins(char **args, t_mini *mini)
{
	int	result;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])))
		return (ft_cd(args, mini->env));
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])))
		return (ft_env(mini->env));
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])))
		return (ft_cd(args, mini->env));
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])))
		return (ft_pwd());
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])))
		return (ft_export(args, mini->env, mini->secret_env));
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])))
		return (ft_unset(args, mini));
	return (0);

}
