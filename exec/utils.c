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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	return (0);
}

int	has_pipe(t_token *token, int type)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
