#include "builtins.h"

int	main(void)
{
	char	*s1[] = {"echo", "Hello World", NULL};
	char	*s2[] = {"echo", "-n", "Hollo Worlo", NULL};
	ft_echo(s1);
	ft_echo(s2);
	return(1);
}
