#include "includes/builtins.h"

void	initialize_mini(t_mini *mini)
{
	mini->exit = 0;
	mini->in = 0;
	mini->out = 0;
	mini->ret = 0;
	mini->secret_env = NULL;
	mini->env = NULL;
}

int	main(int ac, char **av)
{
	t_mini mini;

	initialize_mini(&mini);
	if (ac > 1)
	{
		if (ft_strncmp(av[1], "exit", ft_strlen(av[1])) == 0)
			ft_mini_exit(&mini, av);
	}
	return(SUCCESS);
}
