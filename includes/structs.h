/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:40:00 by sgasperi          #+#    #+#             */
/*   Updated: 2024/03/26 11:47:58 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token
{
	char			*str;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_sig
{
	int		sigin;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}	t_sig;

typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_env	*secret_env;
	int		in;
	int		out;
	int		fd_in;
	int		fd_out;
	int		pipin;
	int		pipout;
	int		pid;
	int		charge;
	int		parent;
	int		last;
	int		ret;
	int		exit;
	int		no_exec;
}	t_mini;
