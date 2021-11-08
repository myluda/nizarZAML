/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:14:36 by nainhaja          #+#    #+#             */
/*   Updated: 2021/11/07 14:14:37 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_heredoc(int *i, char *str)
{
	char	*s;
	int		start;

	while (str[*i] && str[*i] == ' ')
		*i = *i + 1;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '<')
		*i = *i + 1;
	s = ft_substr(str, start, *i - start);
	return (s);
}

void	get_heredocs(int i, int flag, int cpt)
{
	char	*str;

	while (g_shell->buffer[i])
	{
		if (is_quote(g_shell->buffer[i]) && flag == 0)
			flag = 1;
		else if (is_quote(g_shell->buffer[i]) && flag == 1)
			flag = 0;
		else
		{
			if (g_shell->buffer[i] == '<'
				&& flag == 0 && g_shell->buffer[i + 1] == '<'
				&& g_shell->buffer[i + 1] != '\0')
			{
				i = i + 2;
				str = g_shell->heredoc[cpt];
				g_shell->heredoc[cpt] = store_heredoc(&i, g_shell->buffer);
				cpt++;
				free(str);
			}
		}
		if (g_shell->buffer[i])
			i++;
	}
}

void	init_var_hrd(int *i, int *start, int cpt, int c)
{
	char	*str;
	char	*s;

	s = ft_itoa(cpt);
	str = ft_strjoin("/tmp/file", s);
	g_shell->fds[cpt] = open(str,
			O_RDONLY, 0777);
	dup2(g_shell->fds[cpt], c);
	free(s);
	free(str);
	*start = *i;
}

int	ft_remove_qd_file(char *str, int i, t_list *g_shell)
{
	char	*s;
	char	*ptr;

	while (str[i] != ' ' && str[i])
	{
		if (str[i] == '\'')
			i = skip_quotes(i, '\'', str);
		else if (str[i] == '"')
			i = skip_quotes(i, '"', str);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (i);
		else if (str[i] != '\0')
			i++;
	}
	return (i);
}

int	ft_remove_quotes_heredoc(char *str, int i, t_list *g_shell)
{
	char	*s;
	char	*ptr;
	int		cpt;

	cpt = 0;
	while (str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
			i = remove_sqfile(str, i, g_shell);
		else if (str[i] == '"')
			i = remove_dqfile(str, i, g_shell);
		else if (str[i] != '\0')
			i++;
	}
	if (g_shell->g_red_start != (int)ft_strlen(str))
	{
		s = g_shell->heredoc[cpt];
		ptr = ft_substr(str, g_shell->g_red_start, i - g_shell->g_red_start);
		g_shell->heredoc[cpt] = ft_strjoin(g_shell->heredoc[cpt],
				ptr);
		free(ptr);
		free(s);
		cpt++;
	}
	return (i);
}
