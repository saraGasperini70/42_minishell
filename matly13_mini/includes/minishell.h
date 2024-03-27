/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:23:10 by mbasile           #+#    #+#             */
/*   Updated: 2024/03/26 13:17:11 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>

# define EQUAL 0

# define PROMPT "Minishell ~ 42Roma >> "

typedef struct s_env_el
{
	char			*key;
	char			*value;
	struct s_env_el	*next;
	struct s_env_el	*prev;
}	t_env_el;

typedef struct s_env
{
	t_env_el			*head;
	char				**env;
	int					size;
}	t_env;

typedef struct sigaction	t_sigaction;

typedef enum e_bool
{
	false = 0,
	true = 1,
}	t_bool;

enum e_token
{
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	RED_IN = '<',
	RED_OUT = '>',
	HERE_DOC,
	DRED_OUT,
	W = -1,
	_NULL = '0',
};

enum e_sh_state
{
	SH_READING,
	SH_EXECUTING,
};

typedef struct s_elem		t_elem;
typedef struct s_red_el		t_red_el;
typedef union u_union		t_union;
typedef struct s_ast_node	t_ast_node;
typedef struct s_pipe		t_pipe;
typedef struct s_red_lst	t_red_lst;

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	ESCAPED,
	GENERAL,
};

enum e_node_type
{
	CMD,
	PIPE,
};

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_cmd
{
	char			**args;
	char			**env;
	t_fd			fd;
	t_red_lst		*redir;
}	t_cmd;

typedef struct s_pipe
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pipe;

typedef union u_union
{
	t_pipe	*pipe;
	t_cmd	*cmd;
}	t_union;

typedef struct s_ast_node
{
	enum e_node_type	type;
	t_union				*content;
}	t_ast_node;

typedef struct s_ast
{
	t_ast_node	*root;	
}	t_ast;

typedef struct s_elem
{
	char			*content;
	int				len;
	enum e_token	type;
	enum e_state	state;
	t_elem			*next;
	t_elem			*prev;
}	t_elem;

typedef struct s_list
{
	t_elem	*head;
	t_elem	*tail;
	int		size;
}	t_list;

typedef struct s_data
{
	int					exit_status;
	enum e_sh_state		shell_state;
	char				*siglist[NSIG];
	int					pid;
	int					which;
	t_env				*ev;
	t_list				*lex;
	t_ast				*t;
	int					alloc;
	char				**env;
}	t_data;

t_data						g_data;

typedef struct s_red_el
{
	char			*arg;
	enum e_token	type;
	t_red_el		*next;
}	t_red_el;

typedef struct s_red_lst
{
	t_red_el	*head;
	t_red_el	*tail;
	int			size;
}	t_red_lst;

void		add_env_elem(t_env *env, t_env_el *n);
void		add_redir_tail(t_red_lst *list, t_red_el *new);
char		**arr_conv(t_env *env);
void		cap_sig(t_sigaction *sa);
int			check_cmd(t_elem *ptr, char **env);
int			check_args(char **args);
int			check_ccmd(char *cmd);
void		check_cmd_status(t_elem**ptr, char **env, int *value);
int			check_echo(char **args);
int			check_sign(char **args);
int			check_export(t_elem *ptr, char **env);
void		check_fd_built(t_cmd *cmd);
void		check_fd_exec(t_cmd *cmd, int fd[2]);
void		check_i(t_env *env, char *args_i, char **tmp, int index);
void		check_pid(int pid, int count, int count_cmd);
int			count_cmd(t_ast_node *ptr);
int			count_argouments(t_elem *elem);
void		count_redir_args(t_elem **elem, enum e_token type, int *i);
int			count_words(char *str, char *stri);
t_ast_node	*create_cmd(char **args, char **env, t_red_lst *redir);
void		dup_fds(int *old, int new);
void		env_action(t_elem **ptr, t_env *env, char **args, int *i);
int			exec_builtin(t_ast_node *ptr, char ***env, t_elem *head, int fd[2]);
void		exec_redir_in(t_red_el *tmp, int *in);
void		exec_redir_out(t_red_lst *list, t_fd *fd);
void		exec_all(t_ast_node *ptr, char ***env, int count_cmd, t_elem *head);
void		exec_built(t_cmd *cmd, char ***env, t_elem *head);
int			exec_cmd(t_cmd *cmd, char **env, int fd[2]);
char		*exp_env(char *line, char **env);
void		fcmd(t_cmd *cmd);
char		*findc(char *cmd, char **env);
t_elem		*findek(t_elem *head, char *arg, char **env);
char		*findp(char *cmd, char **env);
int			*findrl(t_ast_node *ptr);
char		*find_sc(char *cmd, char **env);
void		fl(t_list *list);
void		flx(t_list *lex_checker);
void		flx_parser(t_list *lex_checker, t_ast *tree);
void		fp(t_ast *tree);
void		f2d(char **arg);
void		frlst(t_red_lst *list);
void		ftree(t_ast_node *n);
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_cd(t_cmd *cmd, char ***env);
int			ft_echo(t_cmd *cmd, t_elem *lex, char **env);
int			ft_env(t_cmd *cmd, char **env);
int			ft_exit(t_cmd *cmd, char **env);
int			ft_export(char ***ev, t_cmd *cmd, t_elem *head);
char		*ft_get_env(char *key, t_env *env);
int			ft_isalpha(char c);
int			ft_isdigit(char c);
int			ft_isnum(char *num);
int			ft_isspace(char c);
char		*ft_itoa(int nb);
char		*ft_join_dir(char *s1, char *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
int			ft_perror(char *msg, char *utils);
void		ft_increaser(int *i, int plus);
int			ft_puterr(char *cmd, char *arg, char *msg, int err_num);
int			ft_pwd(t_cmd *cmd);
int			ft_readline(char **line);
void		*ft_realloc(void *ptr, int old_size, int new_size);
void		ft_sort(t_env *env);
char		**ft_split(char *str, char *stri);
int			ft_strchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *str);
char		*ft_strdup_split(char *str, int *index, char *stri);
int			ft_strisspace(char *str);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strndup(char *s1, int n);
char		*ft_substr(char *s, int start, int len);
void		ft_swap(t_env_el *a, t_env_el *b);
int			ft_unset(t_cmd *cmd, char ***ev);
void		ft_wait(void);
void		ft_hub_cmd(t_cmd *cmd, char ***env, t_elem *head);
int			get_env_var(t_list *tokens, char *str, enum e_state state);
char		*get_exp_value(char **line, char **env);
char		*get_next_line(int fd);
char		*get_redir(enum e_token type);
int			get_word(t_list *tokens, char *str, enum e_state state);
void		handle_env(t_env *env, t_cmd *cmd, t_elem *head);
void		handle_state(t_elem **ptr, char **env, int *value);
t_elem		*ign_space(t_elem *ptr, int opt);
int			in_charset(char c);
t_list		*init_list(t_list *list);
t_red_lst	*init_red_lst(t_red_lst *list);
t_ast		*init_tree(t_ast *tree);
void		init_sig_list(t_data *data);
void		init_sigaction(t_data *data);
int			is_alphanum(int c);
int			is_empty(t_list *list);
int			is_in_strings(char c, char *str);
int			is_opt(char *opt);
int			is_redir(enum e_token type);
int			is_separator(char c, char *stri);
int			join_args(t_cmd **cmd, t_elem *ptr, char **env, int i);
int			join_for_echo(t_cmd **cmd, t_elem *ptr, char **env, int i);
void		launch_mini(char **env);
int			lenght(int nb, int base);
t_list		*lex_checker(char *line);
void		mask_sig(t_sigaction *sa);
t_elem		*new_elem(char *str, int l, enum e_token type, enum e_state state);
t_red_el	*new_redir_elem(char *arg, enum e_token type);
int			number_of_args(char **args);
int			p_err(t_elem *ptr);
int			parse(t_ast **tree, t_elem *ptr, t_env *env);
t_ast_node	*parse_cmd(t_elem **ptr, t_env *env);
int			pcmd_act(t_elem **ptr, t_env *env, t_red_lst *redir, char **args);
t_red_lst	*parse_here_doc(t_red_lst *redir, char *arg, char **env);
t_ast_node	*parse_pipe(t_elem **ptr);
char		*parse_quote(char *s, t_elem **ptr, enum e_token type, t_env *env);
t_red_lst	*parse_redir(t_elem **ptr, t_red_lst *redir, t_env *env);
void		parse_word(t_elem **ptr, char **args, int *i);
void		print_ast_node(t_ast_node *cmd);
void		print_list(t_list *list);
void		print_node(t_elem *node);
void		print_red_lst(t_red_lst *redir);
void		print_sorted_env(t_env *env);
void		print_tree(t_ast_node *ptr, char **env);
void		quotes_state(t_list *t, char *str, enum e_state *state, int flag);
int			red_err(t_elem *ptr);
t_red_lst	*redir_act(t_elem **ptr, t_env *env, t_red_lst *redir);
void		rem_env(t_env *env);
void		rem_env_elem(t_env *env, t_env_el *elem);
char		*search_var(char *key, char **env);
void		set_dir(t_env *ev, char *cwd, char *owd);
void		set_g_data(char **env);
void		sig_manager(int sig, siginfo_t *siginfo, void *ptr);
char		**split_env(char *arg);
int			syn_err(t_list *list);
void		t_add(t_list *list, t_elem *new);
int			tokenize(t_list *tokens, char *line, int i, enum e_state *state);
int			tknz_redir(t_list *tokens, char *line, int i, enum e_state *state);
void		unset_env(char *args, t_env *env);
t_elem		*uquo_check(t_elem **ptr, enum e_token type);
t_env		*init_env(t_env *env);
t_env_el	*new_env_elem(char *line);
void		add_env_elem(t_env *env, t_env_el *elem);
t_env		*new_env(char **tab);
void		deb_env(t_env *env);
char		**arr_conv(t_env *env);
void		rem_env_elem(t_env *env, t_env_el *elem);
void		rem_env(t_env *env);
void		deb_env_arr(char **env);
char		*ft_get_env(char *key, t_env *env);
t_env_el	*search_el(t_env *env, char *key);
char		*search_var(char *key, char **env);
char		*exp_env(char *line, char **env);
char		*get_exp_value(char **line, char **env);
void		deb_env_arr(char **env);
t_env		*init_env(t_env *env);
t_env_el	*new_env_elem(char *line);
void		add_env_elem(t_env *env, t_env_el *n);
t_env		*new_env(char **tab);

char		*ft_get_env(char *key, t_env *env);
t_env_el	*search_el(t_env *env, char *key);
char		*search_var(char *key, char **env);
char		*get_exp_value(char **line, char **env);
char		*exp_env(char *line, char **env);

void		deb_env(t_env *env);
void		rem_env_elem(t_env *env, t_env_el *elem);
void		rem_env(t_env *env);
void		deb_env_arr(char **env);
char		**arr_conv(t_env *env);

#endif
