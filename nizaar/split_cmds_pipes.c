/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:03:29 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 19:03:30 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_pipe(t_list *g_shell)
{
	int		i;
	char	**argvv;

	i = 0;
	argvv = ft_split(ft_join_pipe(), ' ');
	execute(g_shell, argvv);
}

void	echo_pipe(t_list *g_shell)
{
	g_shell->rest = check_for_n(g_shell);
	use_echo(g_shell);
	close(g_shell->g_fd);
}

void	conditions_pipe(t_list *g_shell)
{
	if (!(ft_strcmp(g_shell->f_cmd, "echo")))
		echo_pipe(g_shell);
	else if (!(ft_strcmp(g_shell->f_cmd, "env")))
		print_env(g_shell);
	else if (!(ft_strcmp(g_shell->f_cmd, "export")))
		ft_export(g_shell);
	else if (!ft_strcmp(g_shell->f_cmd, "unset"))
		unset(g_shell);
	else if (!ft_strcmp(g_shell->f_cmd, "cd"))
		cd(g_shell);
	else
		exec_cmd_pipe(g_shell);
}

void	wait_exec(int indice)
{
	int	status;

	status = 0;
	while (indice > 0)
	{
		wait(&status);
		if (WIFSIGNALED(g_shell->g_exit_code))
			g_shell->g_exit_code = WTERMSIG(status) + 128;
		if (WIFEXITED(status))
			g_shell->g_exit_code = WEXITSTATUS(status);
		indice--;
	}
}

int	get_last_quote(int i, char c, char *str)
{
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}
