/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:36:18 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:05:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern	void	rl_replace_line(const char *text, int clear_undo);

void	mask_sig(t_sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, 3);
}

void	cap_sig(t_sigaction *sa)
{
	sigaction(SIGINT, sa, NULL);
	sigaction(3, sa, NULL);
}

void	init_sigaction(t_data *data)
{
	t_sigaction	sa;

	data->ev = NULL;
	data->exit_status = 0;
	data->t = NULL;
	data->alloc = 0;
	data->which = 0;
	data->pid = 0;
	init_sig_list(data);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &sig_manager;
	sa.sa_flags = 0;
	rl_catch_signals = 0;
	data->exit_status = 0;
	mask_sig(&sa);
	cap_sig(&sa);
}

void	init_sig_list(t_data *data)
{
	char	**sys_siglist;

	sys_siglist = data->siglist;
	ft_memset(sys_siglist, 0, 32 * sizeof(char));
	sys_siglist[1] = "Hangup";
	sys_siglist[3] = "Quit";
	sys_siglist[4] = "Illegal instruction";
	sys_siglist[5] = "BPT trace/trap";
	sys_siglist[6] = "ABORT instruction";
	sys_siglist[8] = "Floating point exception";
	sys_siglist[9] = "Killed";
	sys_siglist[10] = "Bus error";
	sys_siglist[11] = "Segmentation fault";
	sys_siglist[12] = "Bad system call";
	sys_siglist[15] = "Terminated";
	sys_siglist[16] = "Urgent IO condition";
	sys_siglist[17] = "Stopped (signal)";
	sys_siglist[18] = "Stopped";
	sys_siglist[21] = "Stopped (tty input)";
	sys_siglist[22] = "Stopped (tty output)";
	sys_siglist[23] = "I/O ready";
	sys_siglist[24] = "CPU limit";
	sys_siglist[25] = "File limit";
	sys_siglist[30] = "User defined signal 1";
	sys_siglist[31] = "User defined signal 2";
}

void	sig_manager(int sig, siginfo_t *siginfo, void *ptr)
{
	(void) ptr;
	(void) siginfo;
	if (sig == SIGINT)
	{
		if (g_data.shell_state != SH_READING)
		{
			return ;
		}
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.exit_status = 1;
	}
}
