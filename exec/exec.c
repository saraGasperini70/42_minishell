#include "../includes/builtins.h"

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	i = 0;
	if (!start)
		return (NULL);
	token = start->next;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	if (mini->charge == 0)
		return ;
	i = 0;
	cmd = cmd_tab(token);
	while (cmd && cmd[i])
	{
		//cmd = ft_expansions(cmd[i], mini->env, mini->ret); parser function?
		i++;
	}
	if (cmd && cmd[0] == "exit" && has_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	ft_free_alloc(cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}
