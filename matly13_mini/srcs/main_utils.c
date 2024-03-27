/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:35:27 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd(t_ast_node *ptr)
{
	static int	c;

	if (ptr->type != CMD)
	{
		count_cmd(ptr->content->pipe->right);
		count_cmd(ptr->content->pipe->left);
	}
	else
		c++;
	return (c);
}

int	ft_readline(char **line)
{
	*line = readline("Minishell ~ 42Roma >> ");
	g_data.shell_state = SH_EXECUTING;
	if (!*line)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strcmp(*line, "") == EQUAL || ft_strisspace(*line))
		return (1);
	if (ft_strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	ft_wait(void)
{
	int	s;

	s = 0;
	while (1)
	{
		g_data.pid = waitpid(-1, &s, 0);
		if (g_data.pid == -1 && errno == EINTR)
			continue ;
		if (g_data.pid == -1)
			break ;
	}
	if (WIFSIGNALED(s))
	{
		g_data.exit_status = WTERMSIG(s) + 128;
		if (WTERMSIG(s) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	if (WIFSIGNALED(s) && WTERMSIG(s) == 3)
		printf("%s: %i\n", g_data.siglist[s], s);
	g_data.which = 0;
}

void	set_g_data(char **env)
{
	g_data.env = env;
	g_data.ev = new_env(env);
	g_data.t = init_tree(g_data.t);
	g_data.shell_state = SH_READING;
}

void	launch_mini(char **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		set_g_data(env);
		if (ft_readline(&line))
			continue ;
		g_data.lex = lex_checker(line);
		if (syn_err(g_data.lex))
			flx(g_data.lex);
		else
		{
			if (parse(&g_data.t, g_data.lex->head, g_data.ev) == 1)
				continue ;
			exec_all(g_data.t->root, &env, count_cmd(g_data.t->root),
				g_data.lex->head);
			flx_parser(g_data.lex, g_data.t);
			ft_wait();
		}
		rem_env(g_data.ev);
	}
}
