/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:18:18 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:18:19 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *ptr, char *s)
{
	char	*test;

	test = ft_strjoin(ptr, " ");
	if (ft_check_restt() >= 1)
		test = ft_strjoin(test, s);
	return (test);
}

void	error_cmd(void)
{
	if (g_shell->f_cmd[0] == '/')
	{
		printf("minishell: %s: No such file or directory\n", g_shell->f_cmd);
		exit(g_shell->g_exit_code = 127);
	}
	else if (ft_strcmp(g_shell->f_cmd, ""))
	{
		printf("minishell: %s: command not found\n", g_shell->f_cmd);
		exit(g_shell->g_exit_code = 127);
	}
	else
		exit(g_shell->g_exit_code = 0);
}

void	execute(t_list *g_shell, char **argvv)
{
	int		i;
	char	**envv;

	envv = NULL;
	i = 0;
	if (g_shell->path[0] == NULL)
		printf("minishell: command not found: %s\n", g_shell->f_cmd);
	else
	{
		if (g_shell->f_cmd[0] == '/' || (g_shell->f_cmd[0] == '.' && g_shell->f_cmd[1] == '/'))
			execve(g_shell->f_cmd, argvv, envv);
		else
		{
			while (g_shell->path[i])
			{
				execve(ft_strjoin(g_shell->path[i], g_shell->f_cmd),
					argvv, g_shell->env);
				i++;
			}
		}
	}
	error_cmd();
}

void	exec_cmd(t_list *g_shell)
{
	int		i;
	int		id;
	char	**argvv;

	id = fork();
	i = 0;
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		argvv = ft_split_spaces(ft_join(g_shell->f_cmd, g_shell->buffer), ' ');
		execute(g_shell, argvv);
		dup2(g_shell->stdio[1], 1);
	}
	else if (id > 0)
	{
		wait_exec(1);
		wait(NULL);
	}
	g_shell->g_signal = 0;
}

void	removee_spaces(t_list *g_shell)
{
	int		i;
	int		start;
	char	*res;
	int		flag;
	char	*ptr;

	res = ft_strdup("");
	i = 0;
	flag = 0;
	start = 0;
	ptr = res;
	while (g_shell->rest[i] != '\0')
	{
		while (g_shell->rest[i] == '\'' || g_shell->rest[i] == '"')
		{
			start = i;
			i = skip_quotes(i + 1, g_shell->rest[i], g_shell->rest);
			res = ft_strjoin(res, ft_substr(g_shell->rest, start, i - start));
		}
		i = skip_onlyspaces(i, g_shell, &res);
		i = get_only_char(g_shell->rest, i, &res);
	}
	g_shell->rest = remove_quotes(res);
	free(ptr);
}
