#include "../builtins.h"

int	ft_strenv_len(char **env)
{
	int	i;

	while (env[i])
		i++;
	return (i);
}
