#include "includes/builtins.h"

void	initialize_mini(t_mini *mini)
{
	printf("Hello\n");
	mini->exit = 0;
	mini->in = 0;
	mini->out = 0;
	mini->ret = 0;
	printf("Hello\n");
	mini->secret_env = NULL;
	mini->env = NULL;
	printf("Hello\n");
}

int	main(void)
{
	t_mini *mini;

	mini = NULL;
	printf("Hello\n");
	initialize_mini(mini);
	printf("Hello\n");
	ft_mini_exit(mini, "1");
	printf("Hello\n");
	return(0);
}
