/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:46:13 by nainhaja          #+#    #+#             */
/*   Updated: 2019/11/06 23:53:30 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_node
{
	char			*beforeeq;
	char			*aftereq;
	struct s_node	*next;
}				t_node;

typedef struct t_list{
	char	*buffer;
	char	*f_cmd;
	char	*rest;
	char	*g_red_buff;
	t_node	*head;
	int		stdio[2];
	char	**path;
	int		g_fd;
	int		g_n;
	char	**env;
	int		env_len;
	char	**export;
	int		*g_fd_pipe;
	char	**tab;
	int		g_signal;
	int		g_red_start;
	int		g_exit_code;
	char	**heredoc;
	int		g_read;
	int		*fds;
	int		hd_nbr;
}					t_list;

t_list				*g_shell;
void		echo_pipe(t_list *g_shell);
int			ft_strcmp(const char *str, const char *to_find);
char		**ft_split(char const *s, char c);
int			get_next_line(int fds, char **line);
char		*ft_strdup(char *s);
char		*ft_substr(char *s, unsigned int start, unsigned int len);
char		*ft_strchr(char *str, int c);
size_t		ft_strlen(char *str);
int			key_press(int key, void *ptr);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, unsigned int len);
char		*ft_checkDollar(char *str, char **env);
char		*ft_RmSpace(char *s, int c);
char		*ft_AddSpace(char *s, int i);
char		*ft_beforeeq(char *k);
char		*ft_aftereq(char *k, t_list *g_shell);
char		**ft_split(char const *s, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_beforeeq_two(char *k);
char		*ft_aftereq_two(char *k);
char		*ft_remove_quotes_two(char *buf);
int			ft_checkQuotes(int *i, int *cpt, int *cpt2, char *s);
char		*ft_remove_spaces(int *start, int *i);
void		ft_get_between_spaces(char *haha, int *i, int *start, char **ptr);
void		ft_get_between_slash(char *haha, int *i, int *start, char **ptr);
void		ft_get_string_quotes(char *haha, int *i, int *start, char **ptr);
char		*ft_remove_spacess(char *haha, int start, int i);
char		*ft_remove_slash(char *haha);
char		*ft_remove_quotes(char *buf, char **env);
void		ft_sort(t_list *g_shell);
char		*ft_remove_n(char *str);
void		copy(char **t, int n, t_list *g_shell);
int			get_listcount(void);
void		deletenode( char *t, t_list *g_shell);
int			search_lastred(char *str);
int			search_used_node(char *beforeeq, char *aftereq, t_list *g_shell);
void		addnode(char *beforeeq, char *aftereq, t_list *g_shell);
char		*searchnode(char *t, t_list *g_shell);
int			ft_strrlen(char **v);
void		ft_putstr(char *str);
void		ft_check_split(void);
void		exec_export(int split_cpt);
void		exec_unset(int split_cpt);
void		copy_env_str(t_list *g_shell);
void		exec_cmds(int *stdio, int split_cpt, char **env);
void		split_cmds(t_list *g_shell);
void		ft_check_redr(t_list *g_shell);
void		ft_free(int split_cpt);
void		ft_init(int *split_cpt, int *i, int *awdi);
void		ft_stock_split(char *str, int *i, int cpt);
int			skip_spaces(int i, char *str);
int			ft_remove_quotes_file(char *str, int i, t_list *g_shell);
void		get_rest_command(t_list *g_shell);
int			skip_quotes(int i, char c, char *str);
char		*remove_spaces(t_list *g_shell);
int			skip_spaces(int i, char *str);
char		*checkvariables(char *str, t_list *g_shell);
int			skip_onlyspaces(int i, t_list *g_shell, char **res);
int			get_only_char(char *str, int i, char **res);
char		*remove_quotes(char *str);
char		*inside_dquotes(char *str, int *i);
char		*inside_squotes(char *str, int *i);
int			get_last_quote(int i, char c, char *str);
void		print_export(t_list *g_shell);
void		print_env(t_list *g_shell);
char		*expand_variable(t_list *g_shell, char *str, int *i, char *res);
void		exec_cmd(t_list *g_shell);
void		get_first_command(t_list *g_shell);
char		*check_for_n(t_list *g_shell);
char		*editpwd(t_list *g_shell, char *ptr);
char		**ft_split_spaces(char const *s, char c);
void		ft_export(t_list *g_shell);
void		expand_command(t_list *g_shell);
void		get_rest(t_list *g_shell);
int			ft_check_pipe(t_list *g_shell);
t_list		*ft_split_pipe(t_list *g_shell, int p, int *reminder, int *i);
void		split_cmds_pipes(void);
void		ft_check_redr_pipe(t_list *g_shell, int c);
void		get_first_command_pipe(t_list *g_shell, int c);
void		conditions_pipe(t_list *g_shell);
void		exec_cmd_pipe(t_list *g_shell);
void		ft_last_command(t_list *g_shell, int p, int *reminder);
void		ft_spawn_last(int in, int *fd, t_list *g_shell, int index);
void		ft_last_pipe(int in, int *fd, t_list *g_shell, int index);
void		wait_exec(int indice);
void		ft_spawn_process(int in, int *fd, t_list *g_shell, int index);
int			is_quote(char c);
void		unset(t_list *g_shell);
void		cd(t_list *g_shell);
void		use_echo(t_list *g_shell);
void		init_var(int *i, int *start, t_list *g_shell, int c);
void		execute(t_list *g_shell, char **argvv);
char		*ft_join(char *s, char *ptr);
char		*ft_itoa(int a);
void		check_line(t_list *g_shell);
char		*split_and_join(char *ptr);
int			ft_word_countt(const char *s, char c);
void		get_rest_command_pipe(t_list *g_shell, int c);
void		ft_word_count_sec(const char *s, int *i);
char		**ft_remplirr(const char *s, char c, char **t, int i);
void		split_spaces_sec(char **t, size_t *cpt, int *j, const char *s);
char		**ft_split_spaces(char const *s, char c);
void		ft_letter_count_sec(int *j, int *cpt, const char *s);
char		*ft_strjoin_sec(char *str, char *ptr);
void		removee_spaces(t_list *g_shell);
void		free_tab(void);
void		finalise(char *ptr, int i, int start);
char		*check_for_n(t_list *g_shell);
int			ft_check_restt(void);
int	remove_sqfile(char *str, int i, t_list *g_shell);
int	remove_dqfile(char *str, int i, t_list *g_shell);
void		ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	check_heredoc(t_list *g_shell);
char	*ft_join_pipe(void);
int	ft_remove_qd_file(char *str, int i, t_list *g_shell);
void	init_var_hrd(int *i, int *start, int cpt, int c);
void	check_heredc(t_list *g_shell);
int		heredoc_number();
void	get_heredocs(int i, int flag, int cpt);
int			ft_atoi(const char *str);
int	ft_isdigit(int str);
#endif