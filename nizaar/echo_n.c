/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:12:14 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:12:15 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	continue_n(t_list *g_shell, char **str)
{
	int	i;
	int	j;

	j = 0;
	i = g_shell->g_n;
	while (str[j])
		j++;
	if (g_shell->g_n > 0)
	{
		g_shell->rest = ft_strdup("");
		if (i <= j)
		{
			while (str[i])
			{
				g_shell->rest = ft_strjoin(g_shell->rest, str[i]);
				if (str[i + 1])
					g_shell->rest = ft_strjoin(g_shell->rest, " ");
				i++;
			}
		}
	}
}

int	found_n(int j, char *str)
{
	while (str[j] == 'n')
		j++;
	return (j);
}

void	search_for_n(t_list *g_shell, char **str, int i, int j)
{
	while (str[i])
	{
		if (str[i][j] == '-' && str[i][j + 1] == 'n')
		{
			j = found_n(j + 1, str[i]);
			if (str[i][j] == '\0')
				g_shell->g_n = i + 1;
			else
				break ;
			j = 0;
		}
		else
			break ;
		i++;
	}
}

char	*check_for_n(t_list *g_shell)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_check_restt() > 1)
	{
		str = ft_split(g_shell->rest, ' ');
		search_for_n(g_shell, str, i, j);
		continue_n(g_shell, str);
	}
	return (g_shell->rest);
}

int	skip_spaces(int i, char *str)
{
	while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_quotes(i, str[i], str);
		else
			i++;
	}
	return (i);
}
