/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:33:58 by sgasperi          #+#    #+#             */
/*   Updated: 2024/03/26 12:08:49 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libs/libft/libft.h"
# include "structs.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define ERROR 1
# define SUCCESS 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define BUFF_SIZE 4096
# define UNKNOWN_COMMAND 127
# define END 7
# define PIPE 6
# define IS_DIRECTORY 126

void	ft_free_alloc(char **matrix);
void	ft_free_node(t_mini *mini, t_env *env);
char	*ft_alloc_str(int alloc_size);
int		ft_strisnum(char *str);
void	ft_free_token(t_token *token);

int		ft_pwd(void);

int		ft_env(t_env *env);

int		ft_echo(char **args);
char	*ft_alloc_str(int alloc_size);
int		ft_cd(char **str, t_env *env);

int		ft_export(char **args, t_env *env, t_env *secret);

void	ft_mini_exit(t_mini *mini, char **cmd);

int		ft_unset(char **a, t_mini *mini);

int		ft_env_len(char *env);
int		ft_isin_env(t_env *env, char *old_pwd);
int		ft_env_add(const char *old_pwd, t_env *env);
char	*ft_get_envname(char *dest, char *src);
void	ft_print_sortedenv(t_env *env);
int		ft_is_validenv(char *args);
char	*ft_env_tostr(t_env *lst);
int		ft_strenv_len(char **env);
void	ft_sortenv(char **tab, int env_len);
int		ft_sizeenv(t_env *lst);

void	exec_cmd(t_mini *mini, t_token *token);

int	ft_exec_bin(char **args, t_env *env, t_mini *mini);

char	*path_join(const char *s1, const char *s2);
void	ft_close(int fd);
int		is_type(t_token *token, int type);
int		has_pipe(t_token *token, int type);
#endif
