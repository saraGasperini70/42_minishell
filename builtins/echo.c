#include "builtins.h"
#include <stdio.h>

int	ft_nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int	i;
	int	options_nb;

	i = 1;
	options_nb = 0;
	if (ft_nb_args(args) > 1)
	{

		while (args[i] && ft_strncmp(args[i], "-n", ft_strlen(args[i])) == 0)
		{
			options_nb = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write (1, " ", 1);
			i++;
		}
	}
	if (options_nb == 0)
		write (1, "\n", 2);
	return (1);
}
