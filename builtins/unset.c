#include "../includes/builtins.h"

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!a[1])
		return (SUCCESS);
	if (ft_strncmp(a[1], env->value, ft_sizeenv(env->value)) == 0)
	{
		if (env->next != NULL)
			mini->env = env->next;
		ft_free_node(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, ft_sizeenv(env->next->value)) == 0)
		{

		}
	}
}
