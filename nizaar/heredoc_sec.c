/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:14:46 by nainhaja          #+#    #+#             */
/*   Updated: 2021/11/07 14:14:47 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredocrd(int cpt, char **ptr, int *start, int i)
{
	char	*str;
	char	*p;

	p = *ptr;
	str = ft_substr(g_shell->buffer, *start, i - *start);
	*ptr = ft_strjoin(*ptr, str);
	free(str);
	free(p);
	i = i + 2;
	while (g_shell->buffer[i] == ' ' && g_shell->buffer[i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_qd_file(g_shell->buffer, i, g_shell);
	init_var_hrd(&i, start, cpt, 0);
	return (i);
}

char	*edit_buffer(int i, int start, int cpt)
{
	int		flag;
	char	*ptr;
	char	*s;
	char	*str;

	ptr = ft_strdup("");
	flag = 0;
	while (g_shell->buffer[i])
	{
		if (is_quote(g_shell->buffer[i]) && flag == 0)
			flag = 1;
		else if (is_quote(g_shell->buffer[i]) && flag == 1)
			flag = 0;
		else
		{
			while (g_shell->buffer[i] == '<' && g_shell->buffer[i + 1] == '<'
				&& flag == 0 && g_shell->buffer[i + 1] != '\0')
			{
				i = check_heredocrd(cpt, &ptr, &start, i);
				cpt++;
			}
		}
		if (g_shell->buffer[i] == '\0')
			break;
		i++;
	}
	s = ptr;
	str = ft_substr(g_shell->buffer, start, i - start);
	ptr = ft_strjoin(ptr, str);
	free(s);
	free(str);

	return (ptr);
}

void	clear_heredoc(void)
{
	int		i;
	char	*str;

	i = 0;
	while (i < g_shell->hd_nbr)
	{
		str = g_shell->heredoc[i];
		close(g_shell->fds[i]);
		i++;
		free(str);
	}
	free(g_shell->heredoc);
	free(g_shell->fds);
}

char	*ft_join_pipe(void)
{
	char	*test;

	test = ft_strjoin(g_shell->f_cmd, " ");
	if (ft_check_restt() >= 1)
		test = ft_strjoin(test, g_shell->rest);
	return (test);
}

void	check_heredoc(t_list *g_shell)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	start = 0;
	g_shell->hd_nbr = heredoc_number(i, start);
	g_shell->heredoc = (char **)malloc(sizeof(char *) * (g_shell->hd_nbr + 1));
	while (i < g_shell->hd_nbr)
	{
		g_shell->heredoc[i] = ft_strdup("");
		i++;
	}
	g_shell->heredoc[i] = NULL;
	get_heredocs(0, 0, 0);
	check_heredc(g_shell);
	str = g_shell->buffer;
	g_shell->buffer = edit_buffer(0, 0, 0);
	free(str);
	clear_heredoc();
}
