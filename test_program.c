#include "includes/builtins.h"

void	initialize_mini(t_mini *mini)
{
	mini->env = NULL;
	mini->exit = 0;
	mini->in = 0;
	mini->out = 0;
	mini->ret = 0;
	mini->secret_env = NULL;
}

int	main(void)
{
	t_mini *mini;

	mini = NULL;
	initialize_mini(mini);
	ft_mini_exit(mini, "1");
	return(0);
}
