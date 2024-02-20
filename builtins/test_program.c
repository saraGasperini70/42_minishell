#include "builtins.h"

int	main(void)
{
	t_env	*env = NULL;

	env->value = "Hello";
	env->next = NULL;
	ft_pwd(env);
	return(1);
}
