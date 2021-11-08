/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 19:09:41 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 19:09:42 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_list *g_shell)
{
	char	**line;
	int		i;
	int		tab;

	i = 0;
	line = ft_split(g_shell->rest, ' ');
	if (line[0] != NULL)
	{
		tab = 0;
		while (line[tab] != 0)
		{
			if (!ft_strcmp(line[tab], "PATH"))
				g_shell->path[0] = NULL;
			deletenode(line[tab], g_shell);
			tab++;
		}
	}
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	use_echo(t_list *g_shell)
{
	if (ft_check_restt() > 0)
	{
		if (g_shell->g_n == 0)
		{
			ft_putstr(g_shell->rest);
			ft_putstr("\n");
		}
		else
			ft_putstr(g_shell->rest);
	}
	else
		ft_putstr("\n");
}

void	echo(t_list *g_shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		g_shell->rest = check_for_n(g_shell);
		use_echo(g_shell);
		close(g_shell->g_fd);
		exit(g_shell->g_exit_code = 0);
	}
	else if (pid > 0)
	{
		wait(NULL);
		g_shell->g_exit_code = 0;
	}
}

void	conditions(t_list *g_shell)
{
	char	*str;

	str = ft_strdup("");
	if (!(ft_strcmp(g_shell->f_cmd, "echo")))
		echo(g_shell);
	else if (!(ft_strcmp(g_shell->f_cmd, "env"))
		&& !(ft_strcmp(g_shell->rest, str)))
	{
		print_env(g_shell);
	}
	else if (!(ft_strcmp(g_shell->f_cmd, "export")))
		ft_export(g_shell);
	else if (!ft_strcmp(g_shell->f_cmd, "unset"))
		unset(g_shell);
	else if (!ft_strcmp(g_shell->f_cmd, "cd"))
		cd(g_shell);
	else if (!ft_strcmp(g_shell->f_cmd, "exit"))
	{
		printf("exit\n");
		if (g_shell->rest)
			exit(ft_atoi(g_shell->rest));
		else
			exit(g_shell->g_exit_code);
	}
	else
		exec_cmd(g_shell);
	free(str);
}

void	split_cmds(t_list *g_shell)
{
	if (ft_check_pipe(g_shell) != 0)
		split_cmds_pipes();
	else
	{
		check_heredoc(g_shell);	
		expand_command(g_shell);
		ft_check_redr(g_shell);	 
		get_first_command(g_shell);
		get_rest(g_shell);
		conditions(g_shell);
		if (g_shell->g_read == -1 && ft_strcmp(g_shell->g_red_buff, ""))
			g_shell->g_exit_code = 1;
		free(g_shell->f_cmd);
		free(g_shell->g_red_buff);
		free(g_shell->rest);
		free(g_shell->buffer);
	}
}
