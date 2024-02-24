#include "../builtins.h"

static char	ft_alloc_char(t_env *lst)
{
	char	*env;

	env = malloc(sizeof(char) * ft_sizeenv(lst) + 1);
	if (!env)
		return (NULL);
	return (env);
}

char	*ft_env_tostr(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = ft_alloc_char(lst);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
			if (lst->next->next == NULL)
				env[i++] = '\n';
		}
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}
