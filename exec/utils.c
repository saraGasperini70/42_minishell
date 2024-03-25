#include "../includes/builtins.h"

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (s2);
}
