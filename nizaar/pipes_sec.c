/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_sec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:30:13 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 16:30:14 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_condition(int in, int *fd)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (fd[1] > 2)
		close(fd[1]);
}

void	pipe_condition_sec(int in, int *fd)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (fd[1] != 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (fd[0] > 2)
		close(fd[0]);
}

void	ft_spawn_process(int in, int *fd, t_list *g_shell, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		pipe_condition_sec(in, fd);
		ft_check_redr_pipe(g_shell, index);
		get_first_command_pipe(g_shell, index);
		get_rest_command_pipe(g_shell, index);
		conditions_pipe(g_shell);
		exit(0);
	}
	else if (pid > 0)
		wait(NULL);
}

void	ft_spawn_last(int in, int *fd, t_list *g_shell, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		pipe_condition(in, fd);
		ft_check_redr_pipe(g_shell, index);
		get_first_command_pipe(g_shell, index);
		get_rest_command_pipe(g_shell, index);
		conditions_pipe(g_shell);
	}
}

void	ft_last_pipe(int in, int *fd, t_list *g_shell, int index)
{
	if (g_shell->tab[index + 1] == NULL)
	{
		ft_spawn_last(in, fd, g_shell, index);
		if (in != 0)
			close(in);
	}
}
