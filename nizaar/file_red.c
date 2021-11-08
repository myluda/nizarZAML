/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:32:05 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:32:06 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_sqfile(char *str, int i, t_list *g_shell)
{
	int	start_sq;

	g_shell->g_red_buff = ft_strjoin(g_shell->g_red_buff,
			ft_substr(str, g_shell->g_red_start, i - g_shell->g_red_start));
	start_sq = i + 1;
	while (str[i] != '\'' && str[i] != '\0')
		i++;
	g_shell->g_red_buff = ft_strjoin(g_shell->g_red_buff,
			ft_substr(str, start_sq, i - start_sq));
	i++;
	g_shell->g_red_start = i;
	return (i);
}

int	remove_dqfile(char *str, int i, t_list *g_shell)
{
	int	start_dq;

	g_shell->g_red_buff = ft_strjoin(g_shell->g_red_buff,
			ft_substr(str, g_shell->g_red_start, i - g_shell->g_red_start));
	start_dq = i + 1;
	while (str[i] != '"' && str[i] != '\0')
		i = i + 1;
	g_shell->g_red_buff = ft_strjoin(g_shell->g_red_buff,
			ft_substr(str, start_dq, i - start_dq));
	i++;
	g_shell->g_red_start = i;
	return (i);
}

int	ft_remove_quotes_file(char *str, int i, t_list *g_shell)
{
	char	*s;
	char	*ptr;

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
		s = g_shell->g_red_buff;
		ptr = ft_substr(str, g_shell->g_red_start, i - g_shell->g_red_start);
		g_shell->g_red_buff = ft_strjoin(g_shell->g_red_buff,
				ptr);
		free(ptr);
		free(s);
	}
	return (i);
}
