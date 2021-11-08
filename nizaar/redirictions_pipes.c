/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirictions_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:28:15 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 18:28:16 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_redr_pipe(char **ptr, int *start, int i, int c)
{
	*ptr = ft_strjoin(*ptr, ft_substr(g_shell->tab[c], *start, i - *start));
	i = i + 2;
	while (g_shell->tab[c][i] == ' ' && g_shell->tab[c][i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->tab[c], i, g_shell);
	g_shell->g_fd = open(g_shell->g_red_buff, O_APPEND
			| O_RDONLY | O_WRONLY | O_CREAT, 0777);
	init_var(&i, start, g_shell, 1);
	return (i);
}

int	single_redr_pipe(char **ptr, int *start, int i, int c)
{
	*ptr = ft_strjoin(*ptr, ft_substr(g_shell->tab[c], *start, i - *start));
	i++;
	while (g_shell->tab[c][i] == ' ' && g_shell->tab[c][i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->tab[c], i, g_shell);
	g_shell->g_fd = open(g_shell->g_red_buff,
			O_TRUNC | O_WRONLY | O_CREAT, 0777);
	init_var(&i, start, g_shell, 1);
	return (i);
}

int	check_readrd_pipe(char **ptr, int *start, int i, int c)
{
	*ptr = ft_strjoin(*ptr, ft_substr(g_shell->tab[c], *start, i - *start));
	i = i + 2;
	while (g_shell->tab[c][i] == ' ' && g_shell->tab[c][i])
		i++;
	g_shell->g_red_start = i;
	i = ft_remove_quotes_file(g_shell->tab[c], i, g_shell);
	if (open(g_shell->g_red_buff, O_TRUNC, 0777) == -1)
	{
		printf("No such file or directory \n");
		exit(0);
	}
	g_shell->g_fd = open(g_shell->g_red_buff, O_RDONLY, 0777);
	init_var(&i, start, g_shell, 0);
	g_shell->g_read = 1;
	return (i);
}

int	found_red(int c, int i, char **ptr, int *start)
{
	int		flag;

	flag = 0;
	while (g_shell->tab[c][i])
	{
		if (is_quote(g_shell->tab[c][i]) && flag == 0)
			flag = 1;
		else if (is_quote(g_shell->tab[c][i]) && flag == 1)
			flag = 0;
		else
		{
			while (g_shell->tab[c][i] == '>'
				&& g_shell->tab[c][i] != '\0' && flag == 0)
			{
				if (g_shell->tab[c][i] == '>' && g_shell->tab[c][i + 1] == '>')
					i = double_redr_pipe(ptr, start, i, c);
				if (g_shell->tab[c][i] == '>' && g_shell->tab[c][i + 1] != '>')
					i = single_redr_pipe(ptr, start, i, c);
			}
			if (g_shell->tab[c][i] == '<')
				i = check_readrd_pipe(ptr, start, i, c);
		}
		i++;
	}
	return (i);
}

void	ft_check_redr_pipe(t_list *g_shell, int c)
{
	int		i;
	int		start;
	int		flag;
	char	*ptr;

	i = 0;
	start = 0;
	flag = 0;
	ptr = ft_strdup("");
	g_shell->g_red_buff = ft_strdup("");
	i = found_red(c, i, &ptr, &start);
	g_shell->tab[c] = ft_strjoin(ptr,
			ft_substr(g_shell->tab[c], start, i - start));
}
